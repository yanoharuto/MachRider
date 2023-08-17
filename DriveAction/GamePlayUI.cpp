#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "EndCountDown.h"
#include "CollectSign.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
/// <summary>
/// 遊んでいるときのUI　制限時間とか
/// </summary>
/// <param name="setTimer"></param>
/// <param name="setFirstCoinNum"></param>
GamePlayUI::GamePlayUI(Timer* setTimer, std::weak_ptr<PlayerObserver> player)
{
    //残り時間
    gameTimerUI = new TimerUI(setTimer);
    //ミニマップ
    minimapUI = new MiniMap(player);
    
    //残りの収集アイテムの数と現在取った数
    firstCoinNum = CollectController::GetTotalCollectNum();
    firstNumUI = new NumUI(allCollectItemNum);
    getNumUI = new NumUI(getCollectItemNum);
    remainingNumUI = new NumUI(remainingCollectItemNum);
    slashData = UIManager::CreateUIData(collectItemUI);
    remainingFraze = UIManager::CreateUIData(remainingCollectItemPhrase);

    //収集アイテムの方向を出す
    cSign = new CollectSign(player);

    playerObserver = player;
    countDown = new EndCountDown(setTimer);
    remainingNumDrawTimer = new ReusableTimer(remainingNumDrawTime);
    //操作方法
    playManual = new PlayManual();
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
    SAFE_DELETE(playManual);
    playerObserver.reset();
}
/// <summary>
/// ミニマップの更新や収集アイテムの枚数を更新
/// </summary>
void GamePlayUI::Update()
{
    int tempNum = nowGetCoinNum;
    //収集アイテムの数
    nowGetCoinNum = playerObserver.lock()->GetCollectCount();
    //ゲットしたアイテムの数が増えたらUIを表示
    if (nowGetCoinNum != tempNum)
    {
        isDrawGetNum = true;
        remainingNumDrawTimer->Reuse();
    }
    //表示しきったらfalseにする
    if (remainingNumDrawTimer->IsOverLimitTime())
    {
        isDrawGetNum = false;
    }
    //ゲームの残り時間が短くなったら動く
    countDown->Update();
    //ミニマップ
    minimapUI->Update();
    //収集アイテムの位置を教えてくれる
    cSign->Update();
    //操作方法更新
    playManual->Update();
}
/// <summary>
/// 描画
/// </summary>
void GamePlayUI::Draw()const
{
    if (isDrawGetNum)//収集アイテムを取ってしばらくの間、残りの数を出す
    {
        int safeNum = 0;
        switch (firstCoinNum - nowGetCoinNum)//残りのアイテムの数に応じて取った時のメッセージを変える
        {
        case 0:
            break;
        case 1:
            safeNum = 1;
            //残りの収集アイテムについてのメッセージ
            safeNum %= remainingFraze.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFraze, safeNum);
            break;
        default:
            //残りの収集アイテムについてのメッセージ
            safeNum %= remainingFraze.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFraze, safeNum);
            remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
            break;
        }
        
    }
    //収集アイテムの数等を表示
    UIDrawer::DrawRotaUI(slashData);
    firstNumUI->Draw(firstCoinNum);
    getNumUI->Draw(nowGetCoinNum);
    //残り時間
    gameTimerUI->Draw();
    //ミニマップ
    minimapUI->Draw();
    //残り時間わずかになると動くカウントダウン
    countDown->DrawUI();
    //操作方法描画
    playManual->Draw();
}