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
PostGoalStaging::PostGoalStaging()
{
    SoundPlayer::StopAllSound();
    switchUI = new SpaceKeyUI(1020,900);
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);
    
    nowProcess = ResultScore::time;
    AddScoreUI(nowProcess);
    timer = new Timer(spaceKeyCoolTime);
    gameEndScreen = RaceScreen::GetScreen();
}

PostGoalStaging::~PostGoalStaging()
{
    SAFE_DELETE(switchUI);
}
void PostGoalStaging::Update()
{
    using enum ResultScore::ScoreKind;
    //�X�R�A��\������������
    if (isDrawTotalScore)
    {
        //�X�y�[�X�L�[�������ďI��
        if (UserInput::GetInputState(Space) == Push)
        {
            SoundPlayer::Play2DSE(sceneNextSE);
            isEndProcess = true;
        }
    }
    //�Ō�܂ŃX�R�A��\�������Ƃ��ɏo�鉹����I�������
    else if (!SoundPlayer::IsPlaySound(scoreEndSE))
    {   
        if (!SoundPlayer::IsPlaySound(scoreStartSE))
        {
            //�X�R�A��������Ƃ�����Ă��Ă���Ƃ��ɉ���炷
            SoundPlayer::Play2DSE(scoreStartSE);
        }
        //�X�R�A�̕\�������������Ă���
        float larp = timer->GetElaspedTime() / spaceKeyCoolTime;
        scoreUI[nowProcess].score = static_cast<int>(ResultScore::GetScore(nowProcess) * larp);
        //�X�R�A��\�������邩�{�^���������ꂽ��
        if (UserInput::GetInputState(Space) == Push || timer->IsOverLimitTime())
        {
            scoreUI[nowProcess].score = ResultScore::GetScore(nowProcess);
            //���̏���������Ă���
            GetNextProcess();
            SoundPlayer::StopSound(scoreStartSE);
            SoundPlayer::Play2DSE(scoreEndSE);
            timer->Init();
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
    //�e�X�R�A��\��
    for (auto itr = scoreUI.begin(); itr != scoreUI.end(); itr++)
    {   
        if ((*itr).second.draw)
        {
            (*itr).second.numUI->Draw((*itr).second.score);
            DrawRotaGraph((*itr).second.scoreKindData.x, (*itr).second.scoreKindData.y, (*itr).second.scoreKindData.size, 0, (*itr).second.scoreKindData.dataHandle[0], true);
        }
    }
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
/// �����ׂ�����������
/// </summary>
/// <returns></returns>
void PostGoalStaging::GetNextProcess()
{
    using enum ResultScore::ScoreKind;
    switch (nowProcess)
    {
    case time:
        AddScoreUI(collect);
        nowProcess = collect;
        //���_���[���Ƃ��������玟��
        if (!scoreUI[collect].draw) GetNextProcess();
        break;

    case collect:
        AddScoreUI(hit);
        nowProcess = hit;
        if (!scoreUI[hit].draw) GetNextProcess();
        break;
    case hit:
        AddScoreUI(total);
        nowProcess = total;
        break;
    case total:
        //�X�R�A��\�����I�����
        isDrawTotalScore = true;
        break;
    default:
        break;
    }
}
/// <summary>
/// �X�R�A�Ɋւ���UI�̒ǉ�
/// </summary>
/// <param name="scoreKind">�ǉ�����UI</param>
void PostGoalStaging::AddScoreUI(ResultScore::ScoreKind scoreKind)
{
    ScoreUI scoreData;
    scoreUI.insert(std::make_pair(scoreKind, scoreData));
    using enum ResultScore::ScoreKind;
    switch (scoreKind)
    {
    case time:
        scoreUI[scoreKind].scoreKindData = UIManager::CreateUIData(timeScore);
        scoreUI[scoreKind].numUI = new NumUI(timeScoreNum);
        scoreUI[scoreKind].draw = true;
        scoreUI[scoreKind].score = 0;
        break;
    case collect:
        scoreUI[scoreKind].scoreKindData = UIManager::CreateUIData(collectScore);
        scoreUI[scoreKind].numUI = new NumUI(collectScoreNum);
        scoreUI[scoreKind].draw = true;
        scoreUI[scoreKind].score = 0;
        break;
    case total:
        scoreUI[scoreKind].scoreKindData = UIManager::CreateUIData(totalScore);
        scoreUI[scoreKind].numUI = new NumUI(totalScoreNum);
        scoreUI[scoreKind].draw = true;
        scoreUI[scoreKind].score = 0;
        break;
    case hit:
        scoreUI[scoreKind].scoreKindData = UIManager::CreateUIData(damageScore);
        scoreUI[scoreKind].numUI = new NumUI(damageScoreNum);
        scoreUI[scoreKind].draw = ResultScore::GetScore(hit) > 0;
        scoreUI[scoreKind].score = 0;
        break;
    }
    
}