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
    //スコアを表示しきったら
    if (isDrawTotalScore)
    {
        //スペースキーを押して終了
        if (UserInput::GetInputState(Space) == Push)
        {
            SoundPlayer::Play2DSE(sceneNextSE);
            isEndProcess = true;
        }
    }
    //最後までスコアを表示したときに出る音が鳴り終わったら
    else if (!SoundPlayer::IsPlaySound(scoreEndSE))
    {   
        if (!SoundPlayer::IsPlaySound(scoreStartSE))
        {
            //スコアをちょっとずつ取ってきているときに音を鳴らす
            SoundPlayer::Play2DSE(scoreStartSE);
        }
        //スコアの表示を少しずつしていく
        float larp = timer->GetElaspedTime() / spaceKeyCoolTime;
        scoreUI[nowProcess].score = static_cast<int>(ResultScore::GetScore(nowProcess) * larp);
        //スコアを表示しきるかボタンを押されたら
        if (UserInput::GetInputState(Space) == Push || timer->IsOverLimitTime())
        {
            scoreUI[nowProcess].score = ResultScore::GetScore(nowProcess);
            //次の処理を取ってくる
            GetNextProcess();
            SoundPlayer::StopSound(scoreStartSE);
            SoundPlayer::Play2DSE(scoreEndSE);
            timer->Init();
        }
    }
}

/// <summary>
/// スコアの描画
/// </summary>
void PostGoalStaging::Draw()const
{
    //ゲーム終了時の画面を暗く表示
    SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
    DrawGraph(0, 0, gameEndScreen, false);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
    //各スコアを表示
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
/// 処理を終了したか
/// </summary>
/// <returns></returns>
bool PostGoalStaging::IsEndProcess() const
{
    return isEndProcess;
}
/// <summary>
/// 今やるべき処理を所得
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
        //得点がゼロとかだったら次に
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
        //スコアを表示し終わった
        isDrawTotalScore = true;
        break;
    default:
        break;
    }
}
/// <summary>
/// スコアに関するUIの追加
/// </summary>
/// <param name="scoreKind">追加するUI</param>
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