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
}

RacePrevProcess::~RacePrevProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDownTimer);
    SAFE_DELETE(countDown);
}

void RacePrevProcess::Update()
{
    //�`�悷��摜�̃R�}����p�@���b�����ƂɎ��̃R�}�ɍs��
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Init();
        iconIncrement++;
    }
    //�Q�[���J�n�����I�������
    if (!SoundPlayer::IsPlaySound(fanfare))
    {
        if (countDownTimer == nullptr)
        {
            countDownTimer = new Timer(5);
            countDown = new CountDown(countDownTimer);
            manualData = UIManager::CreateUIData(manual);
        }
        else
        {
            countDown->Update();
            //�^�C�}�[���I�������珈���I��
            proccesEnd = countDownTimer->IsOverLimitTime();
        }
    }
    
}

void RacePrevProcess::Draw()
{
    if (countDown == nullptr)
    {
        int num = iconIncrement % gamePuroseData.dataHandle.size();
        DrawRotaGraph(gamePuroseData.x, gamePuroseData.y, 1, 0, gamePuroseData.dataHandle[num], true);
    }
    else
    {
        countDown->DrawUI();
        DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);
    }
}

bool RacePrevProcess::IsProccesEnd()
{
    return proccesEnd;
}
