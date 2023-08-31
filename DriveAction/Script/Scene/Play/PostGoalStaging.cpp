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
#include "PlayerObserver.h"
#include "Object.h"
#include "UIDrawer.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "ScoreNum.h"
/// <summary>
/// �S�[����̉��o������
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<PlayerObserver> player)
{
    //�X�R�A���m��
    resultScore = new ResultScore(timer, player);

    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::LoadSound(gameEndFanfare);
    

    //�v���C���[�̏����������W�A�C�e��
    getCollectNum = player.lock()->GetCollectCount();
    drawCollectIconNum = 0;
    //�ŏ��̏���
    nowConvertScore = timeBonus;
    //�^�C���{�[�i�X
    timeScoreUI = GetScoreUI(timeScore);
    
    //���W�A�C�e���{�[�i�X
    collectScoreUI = GetScoreUI(collectScore);
    collectData = UIManager::CreateUIData(collectScoreIcon);
    //���v�X�R�A
    totalScoreUI = GetScoreUI(totalScore);
    totalScoreNumUI = new ScoreNum();
    //�n�C�X�R�A�X�VUI
    hiScoreUI = UIManager::CreateUIData(PraiseWord);
    //�Q�[���I�������
    gameEndScreen = RaceScreen::GetScreen();
    //�X�y�[�X�L�[�Ñ�
    pressSpaceKeyUI = new FlashUI(resultSpaceKey);
    //�N���A�^�C���ۑ�
    clearTime = static_cast<float>(timer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = new NumUI(timeScoreNum);
    //�Q�[���I���A�i�E���X
    finishAnnounceData = UIManager::CreateUIData(finishAnnounce);
    finishAnnounceData.x = SCREEN_WIDTH;
    larpMoveAnnounceTimer = new Timer(finishAnounceTime);
    //�Ԑ���
    EffectManager::LoadEffect(confetti);
}

PostGoalStaging::~PostGoalStaging()
{
    SAFE_DELETE(larpConvertScoreTimer);
    SAFE_DELETE(clearTimeUI);
    SAFE_DELETE(pressSpaceKeyUI);
    SAFE_DELETE(larpMoveAnnounceTimer);
    SAFE_DELETE(totalScoreNumUI);
    SAFE_DELETE(resultScore);
    StopEffekseer2DEffect(confettiEffect);
}
/// <summary>
/// �X�R�A�̐��������X�ɏo���Ă�������
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (!isEndFinishAnnounce)//�I���A�i�E���X���o��
    {
        EndAnnounceProcess();
    }
    else if (isEndConvertScore)//���Z�����I����͉��Z��������
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
    else
    {
        //�e�X�R�A�𑍍��X�R�A�ɕϊ�
        switch (nowConvertScore)
        {
        case timeBonus:
            ConvertTimeScotre();
            break;
        case collectBonus:
            ConvertCollectScotre();
            break;
        }
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
        int safeNum = static_cast<int>(larpMoveAnnounceTimer->GetElaspedTime()) % finishAnnounceData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceData,safeNum);
    }
    else//�e�X�R�A�̕`��
    {
        CollectScoreDraw();
        TimeScoreDraw();
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
        //�����X�R�A��UI�Ɛ���
        totalScoreNumUI->Draw(totalScoreUI.score);
    }
    //�S�X�R�A�ϊ��������I�������X�y�[�X�L�[�Ñ�
    if (isEndConvertScore)
    {
        pressSpaceKeyUI->Draw();
        //�O��̃n�C�X�R�A���傫��������
        if (resultScore->IsUpdateHiScore())
        {
            //�n�C�X�R�A�X�V�̕���
            UIDrawer::DrawRotaUI(hiScoreUI);
        }
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
/// �N���A�^�C���̃X�R�A�ϊ�
/// </summary>
void PostGoalStaging::ConvertTimeScotre()
{
    if (!SoundPlayer::IsPlaySound(sceneNextSE))
    {
        //�X�R�A�����Z���I�������A�X�y�[�X�L�[����������I��
        if ((larpConvertScoreTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(Space) == Push))
        {
            //���̏���
            nowConvertScore = collectBonus;
                //�^�C���{�[�i�X��\��������I��
                SoundPlayer::StopSound(scoreStartSE);
                timeScoreUI.score = resultScore->GetScore(timeBonus);
                drawClearTime = 0.0000f;
        }
        //�^�C�}�[�������Ă���Ԃ̓X�R�A���Z
        else
        {
            //�c�莞�Ԃ��X�R�A�Ɋ��Z
            float larpValue = static_cast<float>(larpConvertScoreTimer->GetElaspedTime() / scoreLarpTime);

            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(timeBonus));
            //�`�悷��N���A�^�C�����X�V
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
            //�X�R�A���Z���͂����Ɩ�
            if (!SoundPlayer::IsPlaySound(scoreStartSE))
            {
                SoundPlayer::Play2DSE(scoreStartSE);
            }
        }
    }
    //�e�X�R�A�����v
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// ���W�A�C�e���̃X�R�A�ϊ�
/// </summary>
void PostGoalStaging::ConvertCollectScotre()
{
    //���X�R�A�ɕϊ�����H�����X�L�b�v
    bool isSkip = UserInput::GetInputState(Space) == Push;
    //���ʉ�����I������^�C�~���O�œ��肵����΂��X�R�A�ɕϊ�����
    if (!SoundPlayer::IsPlaySound(scoreEndSE) || isSkip)
    {
        //�`�悵���A�C�e���̐����l�������A�C�e���̐��Ɠ����ȏ�ɂɂȂ�����
        if (isSkip || (drawCollectIconNum >= getCollectNum && !isEndConvertScore))
        {
            //�`�悷��X�R�A�Ȃǂ��L�^�Ɠ���
            collectScoreUI.score = resultScore->GetScore(collectBonus);
            drawCollectIconNum = getCollectNum;
            isEndConvertScore = true;
            ////�Ԑ���G�t�F�N�g�J�n
            confettiEffect = EffectManager::GetPlayEffect2D(confetti);
            SetPosPlayingEffekseer2DEffect(confettiEffect, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 5);
            //�t�@���t�@�[�����ʉ�
            SoundPlayer::Play2DSE(gameEndFanfare);
        }
        else
        {        //���W�A�C�e��������z�u
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
        }
    }
    //�e�X�R�A�����v
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// �Q�[���I���̃A�i�E���X�𗬂��v���Z�X
/// </summary>
void PostGoalStaging::EndAnnounceProcess()
{
    if (!isSoundClapSE)
    {
        SoundPlayer::Play2DSE(clap);
        isSoundClapSE = true;
    }
    //larp�ړ����I��������
    if (larpMoveAnnounceTimer->IsOverLimitTime())
    {
        isEndFinishAnnounce = true;
        larpConvertScoreTimer = new Timer(scoreLarpTime);
        SoundPlayer::Play2DSE(sceneNextSE);
    }
    else//�ړ�������
    {
        float larpTime = static_cast<float>(larpMoveAnnounceTimer->GetElaspedTime() / finishAnounceTime);
        //�����ړ�����
        float graphWidth = finishAnnounceData.width / finishAnnounceData.dataHandle.size() * finishAnnounceData.size;
        float moveBetween = (SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
        finishAnnounceData.x = static_cast<int>(SCREEN_WIDTH * UIDrawer::GetScreenRaito() - larpTime * (moveBetween));
    }
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
/// <summary>
/// �c�莞�ԃX�R�A�̕`��
/// </summary>
void PostGoalStaging::TimeScoreDraw() const
{
    //�N���A�^�C���̕`��
    UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
    clearTimeUI->Draw(drawClearTime);
}
/// <summary>
/// ���W�A�C�e���X�R�A�̕`��
/// </summary>
void PostGoalStaging::CollectScoreDraw() const
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
}
