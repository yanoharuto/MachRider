#include "PrePlayGameProcess.h"
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
PrePlayGameProcess::PrePlayGameProcess(std::weak_ptr<CollectItemObserver> collectObserver)
{
    using enum UIKind;
    //���̊m��
    SoundPlayer::LoadAndInitSound(SoundKind::fanfare);
    SoundPlayer::Play2DSE(SoundKind::fanfare);
    //UI�̏���
    gamePuroseUIData = UIManager::CreateUIData(gamePurose);
    collectIconUIData = UIManager::CreateUIData(collectIcon);
    collectItemNum = new NumUI(collectTargetNumberUI);
    playManual = new PlayManual();
    //�t�F�[�h�C���t�F�[�h�A�E�g�p�̃^�C�}�[
    frameByFrameTimer = new ReusableTimer(gamePuroseUIData.frameSpeed);
    fadeValue = Utility::MAX1BYTEVALUE;
    //�A�C�e���̐���ۑ�
    remainingCollectNum = collectObserver.lock()->GetTotalItemNum();
}
/// <summary>
/// �J�E���g�_�E���Ȃǂ����
/// </summary>
PrePlayGameProcess::~PrePlayGameProcess()
{
    SAFE_DELETE(frameByFrameTimer);
    SAFE_DELETE(countDown);
    UIManager::DeleteUIGraph(&collectIconUIData);
    UIManager::DeleteUIGraph(&gamePuroseUIData);
    countDownTimer.reset();
}
/// <summary>
/// �V�ѕ��ƃJ�E���g�_�E���̕`��
/// </summary>
void PrePlayGameProcess::Update()
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
void PrePlayGameProcess::Draw() const
{
    if (fadeValue > 0)//�t�F�[�h�A�E�g���Ȃ瑀������ƖڕW��`����
    {
        //�Q�[���̖ړI�������ɂ����̂ł���������𔒂Ŗ��߂�
        int colorValue = Utility::MAX1BYTEVALUE;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//���l��������
        DrawBox(0, 0, Utility::SCREEN_WIDTH, Utility::SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
        //�ڕW�����
        UIDrawer::DrawRotaUI(gamePuroseUIData);
        int num = iconGHIndex % collectIconUIData.dataHandle.size();
        UIDrawer::DrawRotaUI(collectIconUIData,num);
        //���W�߂邩
        collectItemNum->Draw(remainingCollectNum);
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
bool PrePlayGameProcess::IsEndProcess()
{
    return processEnd;
}
