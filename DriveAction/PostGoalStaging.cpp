#include <iostream>
#include "PostGoalStaging.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "RaceScreen.h"
#include "SpaceKeyUI.h"
#include "NumUI.h"
#include "Timer.h"
#include "RaceScreen.h"
#include "HitCountObserver.h"
#include "Object.h"
#include "UIDrawer.h"

/// <summary>
/// �S�[����̉��o������
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<HitCountObserver> player)
{
    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);
    
    //�X�R�A���m��
    resultScore = new ResultScore();
    resultScore->FixScore(timer, player);
    //�v���C���[�̏����������W�A�C�e��
    getCollectNum = player.lock()->GetSubjectHitCount(Object::collect);
    //�ŏ��̏���
    nowProcess = collectBonus;
    //�^�C���{�[�i�X
    timeScoreUI = GetScoreUI(timeScore);
    //���W�A�C�e���{�[�i�X
    collectScoreUI = GetScoreUI(collectScore);
    collectData = UIManager::CreateUIData(collectScoreIcon);
    //���v�X�R�A
    totalScoreUI = GetScoreUI(totalScore);
    totalScoreNumUI = new NumUI(totalScoreNum);
    //�Q�[���I�������
    gameEndScreen = RaceScreen::GetScreen();
    //�X�y�[�X�L�[�Ñ�
    pressSpaceKeyUI = new FlashUI(resultSpaceKey);
    //�N���A�^�C���ۑ�
    clearTime = static_cast<float>( timer->GetElaspedTime());
    clearTimeUI = new NumUI(timeScoreNum);
}

PostGoalStaging::~PostGoalStaging()
{
}
/// <summary>
/// �X�R�A�̐��������X�ɏo���Ă�������
/// 
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (isEndUpdateScore)//���Z�����I����͉��Z��������
    {
        SoundPlayer::StopSound(scoreEndSE);
        pressSpaceKeyUI->Update();
        //�X�y�[�X�L�[�������ďI��
        if (UserInput::GetInputState(Space) == Push)
        {
            SoundPlayer::Play2DSE(sceneNextSE);
            isEndProcess = true;
        }
    }
    //�X�R�A���Z���͂����Ɩ�
    else if (!SoundPlayer::IsPlaySound(scoreStartSE))
    {
        SoundPlayer::Play2DSE(scoreStartSE);
    }
    else
    {
        //�����ׂ��������X�V
        UpdateNowProcess();
    }
}

/// <summary>
/// �X�R�A�̕`��
/// </summary>
void PostGoalStaging::Draw()const
{
    //�Q�[���I�����̉�ʂ��Â��\��
    SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
    DrawGraph(0, 0, gameEndScreen, false);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
    //���W�A�C�e���X�R�A��UI
    UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
    //���������A�C�e�����������`��
    for (int i = 0; i < drawCollectIconNum; i++)
    {
        UIData icon = collectData;
        icon.x += static_cast<int>(collectData.width * UIDrawer::GetScreenRaito() * icon.size * i);//�E�ɂ��炵�Ă���
        UIDrawer::DrawRotaUI(icon);
    }
    //�N���A�^�C���������������X�R�A�Ɉڂ��ւ���
    if (nowProcess == timeBonus)
    {
        UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
        clearTimeUI->Draw(drawClearTime);
    }
    //�S�������I�������X�y�[�X�L�[�Ñ�
    if(isEndUpdateScore)pressSpaceKeyUI->Draw();
    //�����X�R�A��UI�Ɛ���
    totalScoreNumUI->Draw(totalScoreUI.score);
    UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
}
/// <summary>
/// �������I��������
/// </summary>
/// <returns></returns>
bool PostGoalStaging::IsEndProcess() const
{
    return isEndProcess;
}
/// <summary>
/// �����ׂ��������X�V
/// </summary>
/// <returns></returns>
void PostGoalStaging::UpdateNowProcess()
{
    switch (nowProcess)
    {
    case collectBonus:

        if (!SoundPlayer::IsPlaySound(scoreEndSE))
        {
            //���W�A�C�e��������z�u
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
            //�`�悵���A�C�e���̐����l�������A�C�e���̐��Ɠ����ȏ�ɂɂȂ�����
            if (drawCollectIconNum >= getCollectNum)
            {
                collectScoreUI.score = resultScore->GetScore(collectBonus);
                //���̏���
                nowProcess = timeBonus;
                larpTimer = new Timer(scoreLarpTime);
                drawClearTime = clearTime;
            }
        }
        break;

    case timeBonus:
        //�^�C�}�[�������Ă���Ԃ̓X�R�A���Z
        if (!larpTimer->IsOverLimitTime())
        {
            //�c�莞�Ԃ��X�R�A�Ɋ��Z
            float larpValue = static_cast<float>(clearTime * (larpTimer->GetElaspedTime() / larpTimer->GetLimitTime()));
            timeScoreUI.score = static_cast<float>(larpValue * resultScore->GetScoreBonus(timeBonus));
            drawClearTime = clearTime - larpValue;
        }
        else
        {
            //�^�C���{�[�i�X��\��������I��
            SoundPlayer::StopSound(scoreStartSE);
            timeScoreUI.score = resultScore->GetScore(timeBonus);
            drawClearTime = 0.0000f;
            isEndUpdateScore = true;
        }
        break;
    default:
        break;
    }
    //�e�X�R�A�����v
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// �X�R�A�Ɋւ���UI������
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
ScoreUI PostGoalStaging::GetScoreUI(UIKind kind)
{
    ScoreUI ui;
    ui.scoreKindData = UIManager::CreateUIData(kind);
    ui.score = 0;
    return ui;
}
