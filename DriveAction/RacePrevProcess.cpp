#include "RacePrevProcess.h"
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
/// <summary>
/// レース前の処理やってくれる
/// </summary>
RacePrevProcess::RacePrevProcess()
{
    SoundPlayer::LoadSound(fanfare);
    SoundPlayer::Play2DSE(fanfare);
    gamePuroseData = UIManager::CreateUIData(gamePurose);
    collectIconData = UIManager::CreateUIData(collectIcon);
    playManual = new PlayManual();
    collectItemNum = new NumUI(collectTargetNumberUI);
    frameByFrameTimer = new ReusableTimer(gamePuroseData.frameSpeed);
    fadeValue = MAX1BYTEVALUE;
}

RacePrevProcess::~RacePrevProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDownTimer);
    SAFE_DELETE(countDown);
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void RacePrevProcess::Update()
{
    fadeValue--;
    //描画する画像のコマ送り用　何秒かごとに次のコマに行く
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Reuse();
        iconGHIndex++;
    }
    //ゲーム開始音が終わったら
    if (!SoundPlayer::IsPlaySound(fanfare))
    {
        //タイマー開始
        if (countDownTimer == nullptr)
        {
            countDownTimer = new Timer(startTimerLimit);
            countDown = new CountDown(countDownTimer);   
        }
        else
        {
            countDown->Update();
            //タイマーが終了したら処理終了
            proccesEnd = countDownTimer->IsOverLimitTime();
        }
    }
}
/// <summary>
/// 遊び方とカウントダウンの描画
/// </summary>
void RacePrevProcess::Draw() const
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
        collectItemNum->Draw(CollectController::GetTotalCollectNum());
    }
    else
    {
        //カウントダウンと操作説明を表示
        if (countDown->IsPlayCountDownSound())
        {
            countDown->DrawUI();
        }
        playManual->Draw();
    }
}

/// <summary>
/// 処理が終了したか
/// </summary>
/// <returns></returns>
bool RacePrevProcess::IsProccesEnd()
{
    return proccesEnd;
}
