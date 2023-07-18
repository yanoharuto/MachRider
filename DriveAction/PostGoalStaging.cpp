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
/// ゴール後の演出をする
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<ObjectObserver> player)
{
    //スコアを確定
    resultScore = new ResultScore();
    resultScore->FixScore(timer, player);

    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::Play2DSE(clap);

    //プレイヤーの所得した収集アイテム
    getCollectNum = player.lock()->GetSubjectHitCount(Object::collect);
    drawCollectIconNum = 0;
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
    clearTime = static_cast<float>(timer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = new NumUI(timeScoreNum);
    //ゲーム終了
    finishAnnounceData = UIManager::CreateUIData(finishAnnounce);
    finishAnnounceData.x = SCREEN_WIDTH;
    startScoreExchangeTimer = new Timer(finishAnounceTime);
    //総合スコアの色
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
/// スコアの数字を徐々に出していく処理
/// 
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (!isEndFinishAnnounce)//終了アナウンスを出す
    {
        if (startScoreExchangeTimer->IsOverLimitTime())
        {
            isEndFinishAnnounce = true;
        }
        else//移動させる
        {
            float larpTime = startScoreExchangeTimer->GetElaspedTime() / finishAnounceTime;
            //総数移動距離
            int graphWidth = finishAnnounceData.width / finishAnnounceData.dataHandle.size() * finishAnnounceData.size;
            int moveBetween = (SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
            finishAnnounceData.x = SCREEN_WIDTH * UIDrawer::GetScreenRaito() - static_cast<int>(larpTime * (moveBetween));
        }
    }
    else if (isEndUpdateScore)//加算処理終了後は加算音を消す
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

    //終了アナウンス
    if (!isEndFinishAnnounce) 
    {
        int safeNum = static_cast<int>(startScoreExchangeTimer->GetElaspedTime()) % finishAnnounceData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceData,safeNum);
    }
    else
    {
        //収集アイテムスコアのUI
        UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
        //所得したアイテムを少しずつ描画
        for (int i = 1; i <= drawCollectIconNum; i++)
        {
            UIData icon = collectData;
            icon.x += static_cast<int>(collectData.width * UIDrawer::GetScreenRaito() * icon.size * i);//右にずらしていく
            UIDrawer::DrawRotaUI(icon);
        }
        //クリアタイムを少しずつ総合スコアに移し替え
        UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
        clearTimeUI->Draw(drawClearTime);

        //全処理が終わったらスペースキー催促
        if (isEndUpdateScore)pressSpaceKeyUI->Draw();
        
        //総合スコアのUIと数字
        totalScoreNumUI->Draw(totalScoreUI.score);
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
    }
    //エフェクト
    DrawEffekseer2D();
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
            //描画したアイテムの数が獲得したアイテムの数と同じ以上にになったら
            if (drawCollectIconNum >= getCollectNum)
            {
                collectScoreUI.score = resultScore->GetScore(collectBonus);
                //次の処理
                nowProcess = timeBonus;
                larpTimer = new Timer(scoreLarpTime);
                

                break;
            }
            //収集アイテムを一個ずつ配置
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
        }
        break;

    case timeBonus:
        
        //スコアを換算し終えたか、スペースキーを押したら終了
        if ((larpTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(Space) == Push) && !isEndUpdateScore)
        {
            //タイムボーナスを表示したら終了
            SoundPlayer::StopSound(scoreStartSE);
            timeScoreUI.score = resultScore->GetScore(timeBonus);
            drawClearTime = 0.0000f;
            isEndUpdateScore = true;
            ////花吹雪エフェクト
            //confettiEffect = EffectManager::GetPlayEffect2D(confetti);
            //SetPosPlayingEffekseer2DEffect(confettiEffect, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 5);
        }
        //タイマーが動いている間はスコア換算
        else
        {
            //残り時間をスコアに換算
            float larpValue = (larpTimer->GetElaspedTime() / scoreLarpTime);
            
            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(timeBonus));
            //描画するクリアタイムを更新
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
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
