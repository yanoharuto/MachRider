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
#include "ObjectObserver.h"
#include "Object.h"
#include "UIDrawer.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// �S�[����̉��o������
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<ObjectObserver> player)
{
    //�X�R�A���m��
    resultScore = new ResultScore();
    resultScore->FixScore(timer, player);

    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);

    //�v���C���[�̏����������W�A�C�e��
    getCollectNum = player.lock()->GetSubjectHitCount(Object::collect);
    drawCollectIconNum = 0;
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
    clearTime = static_cast<float>(timer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = new NumUI(timeScoreNum);
    //�Q�[���I��
    finishAnnounceData = UIManager::CreateUIData(finishAnnounce);
    finishAnnounceData.x = SCREEN_WIDTH;
    startScoreExchangeTimer = new Timer(finishAnounceTime);
    //�����X�R�A�̐F
    totalScoreColor = bronze;
    EffectManager::LoadEffect(confetti);
}

PostGoalStaging::~PostGoalStaging()
{
    SAFE_DELETE(larpTimer);
    SAFE_DELETE(clearTimeUI);
    SAFE_DELETE(pressSpaceKeyUI);
    SAFE_DELETE(startScoreExchangeTimer);
    SAFE_DELETE(totalScoreNumUI);
    SAFE_DELETE(resultScore);
    StopEffekseer2DEffect(confettiEffect);
}
/// <summary>
/// �X�R�A�̐��������X�ɏo���Ă�������
/// 
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (!isEndFinishAnnounce)//�I���A�i�E���X���o��
    {
        if (startScoreExchangeTimer->IsOverLimitTime())
        {
            isEndFinishAnnounce = true;
        }
        else//�ړ�������
        {
            float larpTime = startScoreExchangeTimer->GetElaspedTime() / finishAnounceTime;
            //�����ړ�����
            int graphWidth = finishAnnounceData.width / finishAnnounceData.dataHandle.size() * finishAnnounceData.size;
            int moveBetween = (SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
            finishAnnounceData.x = SCREEN_WIDTH * UIDrawer::GetScreenRaito() - static_cast<int>(larpTime * (moveBetween));
        }
    }
    else if (isEndUpdateScore)//���Z�����I����͉��Z��������
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

    //�I���A�i�E���X
    if (!isEndFinishAnnounce) 
    {
        int safeNum = static_cast<int>(startScoreExchangeTimer->GetElaspedTime()) % finishAnnounceData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceData,safeNum);
    }
    else
    {
        //���W�A�C�e���X�R�A��UI
        UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
        //���������A�C�e�����������`��
        for (int i = 1; i <= drawCollectIconNum; i++)
        {
            UIData icon = collectData;
            icon.x += static_cast<int>(collectData.width * UIDrawer::GetScreenRaito() * icon.size * i);//�E�ɂ��炵�Ă���
            UIDrawer::DrawRotaUI(icon);
        }
        //�N���A�^�C���������������X�R�A�Ɉڂ��ւ�
        UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
        clearTimeUI->Draw(drawClearTime);

        //�S�������I�������X�y�[�X�L�[�Ñ�
        if (isEndUpdateScore)pressSpaceKeyUI->Draw();
        
        //�����X�R�A��UI�Ɛ���
        totalScoreNumUI->Draw(totalScoreUI.score);
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
    }
    //�G�t�F�N�g
    DrawEffekseer2D();
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
            //�`�悵���A�C�e���̐����l�������A�C�e���̐��Ɠ����ȏ�ɂɂȂ�����
            if (drawCollectIconNum >= getCollectNum)
            {
                collectScoreUI.score = resultScore->GetScore(collectBonus);
                //���̏���
                nowProcess = timeBonus;
                larpTimer = new Timer(scoreLarpTime);
                

                break;
            }
            //���W�A�C�e��������z�u
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
        }
        break;

    case timeBonus:
        
        //�X�R�A�����Z���I�������A�X�y�[�X�L�[����������I��
        if ((larpTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(Space) == Push) && !isEndUpdateScore)
        {
            //�^�C���{�[�i�X��\��������I��
            SoundPlayer::StopSound(scoreStartSE);
            timeScoreUI.score = resultScore->GetScore(timeBonus);
            drawClearTime = 0.0000f;
            isEndUpdateScore = true;
            ////�Ԑ���G�t�F�N�g
            //confettiEffect = EffectManager::GetPlayEffect2D(confetti);
            //SetPosPlayingEffekseer2DEffect(confettiEffect, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 5);
        }
        //�^�C�}�[�������Ă���Ԃ̓X�R�A���Z
        else
        {
            //�c�莞�Ԃ��X�R�A�Ɋ��Z
            float larpValue = (larpTimer->GetElaspedTime() / scoreLarpTime);
            
            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(timeBonus));
            //�`�悷��N���A�^�C�����X�V
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
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
