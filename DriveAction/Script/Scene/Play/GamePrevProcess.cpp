#include "GamePrevProcess.h"
#include "DxLib.h"
#include "SoundPlayer.h"
#include "Utility.h"
#include "Timer.h"
#include "CountDown.h"
#include "NumUI.h"
#include "CollectController.h"
#include "UIDrawer.h"
#include "PlayManual.h"
#include "ReusableTimer.h"
#include "CollectItemObserver.h"
/// <summary>
/// 操作説明やカウントダウン。音などを準備
/// </summary>
/// <param name="collectObserver">何個回収するか教えてもらう</param>
GamePrevProcess::GamePrevProcess(std::weak_ptr<CollectItemObserver> collectObserver)
{
    //音の確保
    SoundPlayer::LoadAndInitSound(fanfare);
    SoundPlayer::Play2DSE(fanfare);
    //UIの準備
    gamePuroseData = UIManager::CreateUIData(gamePurose);
    collectIconData = UIManager::CreateUIData(collectIcon);
    collectItemNum = new NumUI(collectTargetNumberUI);
    playManual = new PlayManual();
    //フェードインフェードアウト用のタイマー
    frameByFrameTimer = new ReusableTimer(gamePuroseData.frameSpeed);
    fadeValue = MAX1BYTEVALUE;
    //アイテムの数を保存
    allCollectItemNum = collectObserver.lock()->GetTotalItemNum();
}
/// <summary>
/// カウントダウンなどを解放
/// </summary>
GamePrevProcess::~GamePrevProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDown);
    countDownTimer.reset();
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void GamePrevProcess::Update()
{
    fadeValue--;
    //描画する画像のコマ送り用　何秒かごとに次のコマに行く
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Reuse();
        iconGHIndex++;
    }
    //ゲーム開始音が終わったら
    if (fadeValue < 1)
    {
        //タイマー開始
        if (countDownTimer == nullptr)
        {
            countDownTimer = std::make_shared<Timer>(startTimerLimit);
            countDown = new CountDown(countDownTimer);
        }
        else
        {
            countDown->Update();
            //タイマーが終了したら処理終了
            processEnd = countDownTimer->IsOverLimitTime();
        }
    }
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void GamePrevProcess::Draw() const
{
    if (fadeValue > 0)//フェードアウト中なら操作説明と目標を伝える
    {
        //ゲームの目的が見えにくいのでいったん後ろを白で埋める
        int colorValue = MAX1BYTEVALUE;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
        //目標を説明
        UIDrawer::DrawRotaUI(gamePuroseData);
        int num = iconGHIndex % collectIconData.dataHandle.size();
        UIDrawer::DrawRotaUI(collectIconData,num);
        //何個集めるか
        collectItemNum->Draw(allCollectItemNum);
    }
    else
    {
        //カウントダウンと操作説明を表示
        countDown->DrawUI();
        playManual->Draw();
    }
}

/// <summary>
/// 処理が終了したか
/// </summary>
/// <returns>処理が終了したならTrue</returns>
bool GamePrevProcess::IsEndProcess()
{
    return processEnd;
}
