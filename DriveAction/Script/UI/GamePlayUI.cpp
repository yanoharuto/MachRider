#include "GamePlayUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "EndCountDown.h"
#include "CollectCompass.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// プレイヤーや制限時間、収集アイテムの数などを表示できるようにする
/// </summary>
/// <param name="player">プレイヤーの位置</param>
/// <param name="timer">制限時間</param>
/// <param name="collectItemObserver">収集アイテム情報</param>
GamePlayUI::GamePlayUI(std::weak_ptr<PlayerObserver> player, std::weak_ptr<Timer> timer, std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    using enum UIKind;
    //残り時間
    gameTimerUI = new TimerUI(timer);
    //ミニマップ
    minimapUI = new MiniMap(player);
    //残りの収集アイテムの数
    firstCoinNum = collectItemObserver->GetTotalItemNum();
    firstCollectNumUI = new NumUI(allCollectItemNum);
    //現在取った数
    getNumUI = new NumUI(getCollectItemNum);
    remainingNumUI = new NumUI(remainingCollectItemNum);
    //収集アイテムに関するUIの枠
    frameUIData = UIManager::CreateUIData(collectItemFrameUI);
    //残り収集アイテムについてのコメントUI
    remainingFrazeUIData = UIManager::CreateUIData(remainingCollectItemPhrase);
    //プレイヤーのアイテム所得情報を教えてもらう
    playerObserver = player;
    //収集アイテムの方向を出す
    collectCompass = new CollectCompass(player,collectItemObserver);
    //ゲーム終了カウントダウン
    countDown = new EndCountDown(timer);
    //残り時間
    remainingNumDrawTimer = new ReusableTimer(remainingNumDrawTime);
    //操作方法
    playManual = new PlayManual();
}

/// <summary>
/// 各UIを開放
/// </summary>
GamePlayUI::~GamePlayUI()
{
    SAFE_DELETE(gameTimerUI);
    SAFE_DELETE(minimapUI);
    SAFE_DELETE(getNumUI);
    SAFE_DELETE(firstCollectNumUI);
    SAFE_DELETE(remainingNumUI);
    SAFE_DELETE(countDown);
    SAFE_DELETE(collectCompass);
    SAFE_DELETE(remainingNumDrawTimer);
    SAFE_DELETE(playManual);
    playerObserver.reset();
    UIManager::DeleteUIGraph(&remainingFrazeUIData);
    UIManager::DeleteUIGraph(&frameUIData);
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
    collectCompass->Update();
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
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            break;
        default:
            //残りの収集アイテムについてのメッセージ
            safeNum %= remainingFrazeUIData.dataHandle.size();
            UIDrawer::DrawRotaUI(remainingFrazeUIData, safeNum);
            remainingNumUI->Draw(firstCoinNum - nowGetCoinNum);
            break;
        }
        
    }
    //収集アイテムの数等を表示
    UIDrawer::DrawRotaUI(frameUIData);
    firstCollectNumUI->Draw(firstCoinNum);
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