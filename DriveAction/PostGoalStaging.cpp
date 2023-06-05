#include <iostream>
#include "PostGoalStaging.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "ResultScore.h"
#include "RaceScreen.h"
#include "SwitchUI.h"
#include "NumUI.h"
PostGoalStaging::PostGoalStaging()
{
    SoundPlayer::StopAllSound();
    switchUI = new SwitchUI();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);
    

    InitScoreUI(collectScore, 0);
    InitScoreUI(damageScore, 1);
    InitScoreUI(totalScore, 2);
    InitScoreUI(timeScore, 3);
    //Y���W���������Ƀ\�[�g
    for (int i = 0; i < SCORE_KIND_NUM; i++)
    {
        int iY = scoreUI[i].data.y;
        for (int j = i; j < SCORE_KIND_NUM; j++)
        {
            int jY = scoreUI[j].data.y;
            //i�Ԗڂ̗v�f�����߂�
            if (jY < iY)
            {
                std::swap(scoreUI[j],scoreUI[i] );
            }
        }
    }
    timer = new Timer(spaceKeyCoolTime);
}

PostGoalStaging::~PostGoalStaging()
{
    SAFE_DELETE(switchUI);
}

bool PostGoalStaging::Update()
{

    //�I���̃A�i�E���X�̕\�����I������
    if (!SoundPlayer::IsPlaySound(scoreEndSE) && spaceClickCount < SCORE_KIND_NUM )
    {
        if (!SoundPlayer::IsPlaySound(scoreStartSE))
        {
            SoundPlayer::Play2DSE(scoreStartSE);
        }
        //�X�R�A�̕\�������������Ă���
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = static_cast<int>(ResultScore::GetScore(spaceClickCount) * larp);
        //�X�R�A��\�������邩�{�^���������ꂽ��
        if (UserInput::GetInputState(Space) == Detach || timer->IsOverLimitTime())
        {
            //�X�R�A�̍ŏI�\��
            SoundPlayer::StopSound(scoreStartSE);
            SoundPlayer::Play2DSE(scoreEndSE);
            scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount);
            //���̃X�R�A�̍X�V�̏���
            spaceClickCount++;

            timer->Init();
        }
    }


    
    //�I�����̉������ĂȂ���
    if (!SoundPlayer::IsPlaySound(sceneNextSE))
    {
        //�X�R�A��\�����������特��炵��
        if (spaceClickCount == SCORE_KIND_NUM && UserInput::GetInputState(Space))
        {
            SoundPlayer::Play2DSE(sceneNextSE);
            spaceClickCount++;
            timer->Init();
        }
        //�Ȃ�I�������I��
        if (spaceClickCount > SCORE_KIND_NUM )
        {
            if (timer->IsOverLimitTime())
            {
                return true;
            }
        }
    }
    return false;
}

void PostGoalStaging::Draw()
{
    for (int i = 0; i <= spaceClickCount; i++)
    {
        int safeNum = i % SCORE_KIND_NUM;
        scoreUI[safeNum].ui->Draw(scoreUI[safeNum].score);
        DrawRotaGraph(scoreUI[safeNum].data.x, scoreUI[safeNum].data.y, scoreUI[safeNum].data.size, 0, scoreUI[safeNum].data.dataHandle[0], true);
    }

    if (spaceClickCount != 0)
    {
        switchUI->Draw();
    }
}

void PostGoalStaging::InitScoreUI(UIKind kind,int index)
{
    switch (kind)
    {
    case collectScore:
        scoreUI[index].data = UIManager::CreateUIData(collectScore);
        scoreUI[index].ui = new NumUI(collectScoreNum);
        break;
    case timeScore:
        scoreUI[index].data = UIManager::CreateUIData(timeScore);
        scoreUI[index].ui = new NumUI(timeScoreNum);
        break;
    case totalScore:
        scoreUI[index].data = UIManager::CreateUIData(totalScore);
        scoreUI[index].ui = new NumUI(totalScoreNum);
        break;
    case damageScore:
        scoreUI[index].data = UIManager::CreateUIData(damageScore);
        scoreUI[index].ui = new NumUI(damageScoreNum);
        break;
    }
}
