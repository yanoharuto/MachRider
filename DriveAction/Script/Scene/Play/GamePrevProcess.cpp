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
/// ���������J�E���g�_�E���B���Ȃǂ�����
/// </summary>
/// <param name="collectObserver">��������邩�����Ă��炤</param>
GamePrevProcess::GamePrevProcess(std::weak_ptr<CollectItemObserver> collectObserver)
{
    //���̊m��
    SoundPlayer::LoadAndInitSound(fanfare);
    SoundPlayer::Play2DSE(fanfare);
    //UI�̏���
    gamePuroseData = UIManager::CreateUIData(gamePurose);
    collectIconData = UIManager::CreateUIData(collectIcon);
    collectItemNum = new NumUI(collectTargetNumberUI);
    playManual = new PlayManual();
    //�t�F�[�h�C���t�F�[�h�A�E�g�p�̃^�C�}�[
    frameByFrameTimer = new ReusableTimer(gamePuroseData.frameSpeed);
    fadeValue = MAX1BYTEVALUE;
    //�A�C�e���̐���ۑ�
    allCollectItemNum = collectObserver.lock()->GetTotalItemNum();
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
void GamePrevProcess::Update()
{
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
        collectItemNum->Draw(allCollectItemNum);
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
