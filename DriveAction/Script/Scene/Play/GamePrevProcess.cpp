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
#include "GameManager.h"
/// <summary>
/// ����UI�̏�����
/// </summary>
GamePrevProcess::GamePrevProcess()
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
/// <summary>
/// �J�E���g�_�E���Ȃǂ����
/// </summary>
GamePrevProcess::~GamePrevProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDown);
    countDownTimer.reset();
}
/// <summary>
/// �V�ѕ��ƃJ�E���g�_�E���̕`��
/// </summary>
void GamePrevProcess::Update(std::shared_ptr<GameManager> gameObj)
{
    gameObj->PrepareGame();
    fadeValue--;
    //�`�悷��摜�̃R�}����p�@���b�����ƂɎ��̃R�}�ɍs��
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Reuse();
        iconGHIndex++;
    }
    //�Q�[���J�n�����I�������
    if (fadeValue < 1)
    {
        //�^�C�}�[�J�n
        if (countDownTimer == nullptr)
        {
            countDownTimer = std::make_shared<Timer>(startTimerLimit);
            countDown = new CountDown(countDownTimer);
        }
        else
        {
            countDown->Update();
            //�^�C�}�[���I�������珈���I��
            processEnd = countDownTimer->IsOverLimitTime();
        }
    }
}
/// <summary>
/// �V�ѕ��ƃJ�E���g�_�E���̕`��
/// </summary>
void GamePrevProcess::Draw() const
{
    if (fadeValue > 0)//�t�F�[�h�A�E�g���Ȃ瑀������ƖڕW��`����
    {
        //�Q�[���̖ړI�������ɂ����̂ł���������𔒂Ŗ��߂�
        int colorValue = MAX1BYTEVALUE;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//���l��������
        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
        //�ڕW�����
        UIDrawer::DrawRotaUI(gamePuroseData);
        int num = iconGHIndex % collectIconData.dataHandle.size();
        UIDrawer::DrawRotaUI(collectIconData,num);
        //���W�߂邩
        collectItemNum->Draw(CollectController::GetTotalCollectNum());
    }
    else
    {
        //�J�E���g�_�E���Ƒ��������\��
        countDown->DrawUI();
        playManual->Draw();
    }
}

/// <summary>
/// �������I��������
/// </summary>
/// <returns>�������I�������Ȃ�True</returns>
bool GamePrevProcess::IsEndProcess()
{
    return processEnd;
}
