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
/// ゴール後の演出をする
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<HitCountObserver> player)
{
    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);
    
    //スコアを確定
    resultScore = new ResultScore();
    resultScore->FixScore(timer, player);
    //プレイヤーの所得した収集アイテム
    getCollectNum = player.lock()->GetSubjectHitCount(Object::collect);
    //最初の処理
    nowProcess = collectBonus;
    //タイムボーナス
    timeScoreUI = GetScoreUI(timeScore);
    //収集アイテムボーナス
    collectScoreUI = GetScoreUI(collectScore);
    collectData = UIManager::CreateUIData(collectScoreIcon);
    //合計スコア
    totalScoreUI = GetScoreUI(totalScore);
    totalScoreNumUI = new NumUI(totalScoreNum);
    //ゲーム終了時画面
    gameEndScreen = RaceScreen::GetScreen();
    //スペースキー催促
    pressSpaceKeyUI = new FlashUI(resultSpaceKey);
    //クリアタイム保存
    clearTime = static_cast<float>( timer->GetElaspedTime());
    clearTimeUI = new NumUI(timeScoreNum);
}

PostGoalStaging::~PostGoalStaging()
{
}
/// <summary>
/// スコアの数字を徐々に出していく処理
/// 
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (isEndUpdateScore)//加算処理終了後は加算音を消す
    {
        SoundPlayer::StopSound(scoreEndSE);
        pressSpaceKeyUI->Update();
        //スペースキーを押して終了
        if (UserInput::GetInputState(Space) == Push)
        {
            SoundPlayer::Play2DSE(sceneNextSE);
            isEndProcess = true;
        }
    }
    //スコア加算中はずっと鳴る
    else if (!SoundPlayer::IsPlaySound(scoreStartSE))
    {
        SoundPlayer::Play2DSE(scoreStartSE);
    }
    else
    {
        //今やるべき処理を更新
        UpdateNowProcess();
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
    //収集アイテムスコアのUI
    UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
    //所得したアイテムを少しずつ描画
    for (int i = 0; i < drawCollectIconNum; i++)
    {
        UIData icon = collectData;
        icon.x += static_cast<int>(collectData.width * UIDrawer::GetScreenRaito() * icon.size * i);//右にずらしていく
        UIDrawer::DrawRotaUI(icon);
    }
    //クリアタイムを少しずつ総合スコアに移し替える
    if (nowProcess == timeBonus)
    {
        UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
        clearTimeUI->Draw(drawClearTime);
    }
    //全処理が終わったらスペースキー催促
    if(isEndUpdateScore)pressSpaceKeyUI->Draw();
    //総合スコアのUIと数字
    totalScoreNumUI->Draw(totalScoreUI.score);
    UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
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
/// 今やるべき処理を更新
/// </summary>
/// <returns></returns>
void PostGoalStaging::UpdateNowProcess()
{
    switch (nowProcess)
    {
    case collectBonus:

        if (!SoundPlayer::IsPlaySound(scoreEndSE))
        {
            //収集アイテムを一個ずつ配置
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
            //描画したアイテムの数が獲得したアイテムの数と同じ以上にになったら
            if (drawCollectIconNum >= getCollectNum)
            {
                collectScoreUI.score = resultScore->GetScore(collectBonus);
                //次の処理
                nowProcess = timeBonus;
                larpTimer = new Timer(scoreLarpTime);
                drawClearTime = clearTime;
            }
        }
        break;

    case timeBonus:
        //タイマーが動いている間はスコア換算
        if (!larpTimer->IsOverLimitTime())
        {
            //残り時間をスコアに換算
            float larpValue = static_cast<float>(clearTime * (larpTimer->GetElaspedTime() / larpTimer->GetLimitTime()));
            timeScoreUI.score = static_cast<float>(larpValue * resultScore->GetScoreBonus(timeBonus));
            drawClearTime = clearTime - larpValue;
        }
        else
        {
            //タイムボーナスを表示したら終了
            SoundPlayer::StopSound(scoreStartSE);
            timeScoreUI.score = resultScore->GetScore(timeBonus);
            drawClearTime = 0.0000f;
            isEndUpdateScore = true;
        }
        break;
    default:
        break;
    }
    //各スコアを合計
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// スコアに関するUIを所得
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
