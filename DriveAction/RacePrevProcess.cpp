#include "RacePrevProcess.h"
#include "DxLib.h"
#include "SoundPlayer.h"
#include "Utility.h"
#include "Timer.h"
#include "CountDown.h"
RacePrevProcess::RacePrevProcess()
{
    SoundPlayer::LoadSound(fanfare);
    SoundPlayer::Play2DSE(fanfare);
    gamePuroseData = UIManager::CreateUIData(gamePurose);

    frameByFrameTimer = new Timer(gamePuroseData.frameSpeed);
    fadeValue = MAX1BYTEVALUE;
}

RacePrevProcess::~RacePrevProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDownTimer);
    SAFE_DELETE(countDown);
}

void RacePrevProcess::Update()
{
    fadeValue--;
    //描画する画像のコマ送り用　何秒かごとに次のコマに行く
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Init();
        iconIncrement++;
    }
    //ゲーム開始音が終わったら
    if (!SoundPlayer::IsPlaySound(fanfare))
    {
        //タイマー開始
        if (countDownTimer == nullptr)
        {
            countDownTimer = new Timer(startTimerLimit);
            countDown = new CountDown(countDownTimer);
            manualData = UIManager::CreateUIData(manual);
        }
        else
        {
            countDown->Update();
            //タイマーが終了したら処理終了
            proccesEnd = countDownTimer->IsOverLimitTime();

        }
    }
    
}

void RacePrevProcess::Draw() const
{
    if (countDown == nullptr)
    {
        //ゲームの目的が見えにくいのでいったん後ろを白で埋める
        int colorValue = MAX1BYTEVALUE;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
        int num = iconIncrement % gamePuroseData.dataHandle.size();
        DrawRotaGraph(gamePuroseData.x, gamePuroseData.y, 1, 0, gamePuroseData.dataHandle[num], true);
    }
    else
    {
        if (countDown->IsPlayCountDownSound())
        {
            countDown->DrawUI();
        }
        DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    }
}

bool RacePrevProcess::IsProccesEnd()
{
    return proccesEnd;
}
