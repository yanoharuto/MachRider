#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "ObjectObserver.h"
#include "EndCountDown.h"
#include "CollectSign.h"

/// <summary>
/// 遊んでいるときのUI　制限時間とか
/// </summary>
/// <param name="setTimer"></param>
/// <param name="setFirstCoinNum"></param>
GamePlayUI::GamePlayUI(Timer* setTimer, std::weak_ptr<ObjectObserver> player)
{
    //残り時間
    gameTimerUI = new TimerUI(setTimer);
    //ミニマップ
    minimapUI = new MiniMap(player);
    manualData = UIManager::CreateUIData(manual);

    
    //残りの収集アイテムの数と現在取った数
    firstCoinNum = CollectController::TotalCollectNum();
    firstNumUI = new NumUI(allCollectItemNum);
    getNumUI = new NumUI(getCollectItemNum);
    remainingNumUI = new NumUI(remainingCollectItemNum);
    slashData = UIManager::CreateUIData(collectItemUI);
    remainingFraze = UIManager::CreateUIData(remainingCollectItemPhrase);

    //収集アイテムの方向を出す
    cSign = new CollectSign(player);

    playerObserver = player;
    countDown = new EndCountDown(setTimer);
    remainingNumDrawTimer = new Timer(remainingNumDrawTime);
}


GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(gameTimerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstNumUI);
    SAFE_DELETE(remainingNumUI);
    SAFE_DELETE(countDown);
    SAFE_DELETE(cSign);
    SAFE_DELETE(remainingNumDrawTimer);
    playerObserver.reset();
}
/// <summary>
/// ミニマップの更新や収集アイテムの枚数を更新
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCoinNum;
    nowGetCoinNum = playerObserver.lock()->GetSubjectHitCount(Object::ObjectTag::collect);
    //ゲットしたアイテムの数が増えたらUIを表示
    if (nowGetCoinNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Init();
    }
    //表示しきったらfalseにする
    if (remainingNumDrawTimer->IsOverLimitTime())
    {
        isDrawGetNum = false;
    }
    //ゲームの残り時間が短くなったら終了
    countDown->Update();
    //ミニマップ
    minimapUI->Update();
    //収集アイテムの位置を教えてくれる
    cSign->Update();
}
/// <summary>
/// 描画
/// </summary>
void GamePlayUI::Draw()const
{
    DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    if (isDrawGetNum)//収集アイテムを取ってしばらくの間、残りの数を出す
    {
        int safeNum = 0;
        if (CollectController::GetRemainingCollectNum() == 1)safeNum = 1;//残りのアイテムの数に応じて取った時のメッセージを変える
        if (CollectController::GetRemainingCollectNum() == 0)safeNum = 0;
        safeNum %= remainingFraze.dataHandle.size();
        DrawRotaGraph(remainingFraze.x, remainingFraze.y,remainingFraze.size,0,remainingFraze.dataHandle[safeNum],true);
        remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
    }
    
    DrawRotaGraph(slashData.x, slashData.y, slashData.size, 0, slashData.dataHandle[0], true);
    firstNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum);
    gameTimerUI->Draw();
    minimapUI->Draw();
    countDown->DrawUI();
}