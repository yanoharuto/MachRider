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
/// ゴール後の演出をする
/// </summary>
PostGoalStaging::PostGoalStaging(Timer* timer, std::weak_ptr<PlayerObserver> player)
{
    //スコアを確定
    resultScore = new ResultScore(timer, player);

    SoundPlayer::StopAllSound();
    SoundPlayer::LoadSound(clap);
    SoundPlayer::LoadSound(scoreEndSE);
    SoundPlayer::LoadSound(scoreStartSE);
    SoundPlayer::LoadSound(sceneNextSE);
    SoundPlayer::LoadSound(gameEndFanfare);
    

    //プレイヤーの所得した収集アイテム
    getCollectNum = player.lock()->GetCollectCount();
    drawCollectIconNum = 0;
    //最初の処理
    nowConvertScore = timeBonus;
    //タイムボーナス
    timeScoreUI = GetScoreUI(timeScore);
    
    //収集アイテムボーナス
    collectScoreUI = GetScoreUI(collectScore);
    collectData = UIManager::CreateUIData(collectScoreIcon);
    //合計スコア
    totalScoreUI = GetScoreUI(totalScore);
    totalScoreNumUI = new ScoreNum();
    //ハイスコア更新UI
    hiScoreUI = UIManager::CreateUIData(PraiseWord);
    //ゲーム終了時画面
    gameEndScreen = RaceScreen::GetScreen();
    //スペースキー催促
    pressSpaceKeyUI = new FlashUI(resultSpaceKey);
    //クリアタイム保存
    clearTime = static_cast<float>(timer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = new NumUI(timeScoreNum);
    //ゲーム終了アナウンス
    finishAnnounceData = UIManager::CreateUIData(finishAnnounce);
    finishAnnounceData.x = SCREEN_WIDTH;
    larpMoveAnnounceTimer = new Timer(finishAnounceTime);
    //花吹雪
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
/// スコアの数字を徐々に出していく処理
/// </summary>
/// <returns></returns>
void PostGoalStaging::Update()
{
    if (!isEndFinishAnnounce)//終了アナウンスを出す
    {
        EndAnnounceProcess();
    }
    else if (isEndConvertScore)//加算処理終了後は加算音を消す
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
    else
    {
        //各スコアを総合スコアに変換
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
        int safeNum = static_cast<int>(larpMoveAnnounceTimer->GetElaspedTime()) % finishAnnounceData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceData,safeNum);
    }
    else//各スコアの描画
    {
        CollectScoreDraw();
        TimeScoreDraw();
        UIDrawer::DrawRotaUI(totalScoreUI.scoreKindData);
        //総合スコアのUIと数字
        totalScoreNumUI->Draw(totalScoreUI.score);
    }
    //全スコア変換処理が終わったらスペースキー催促
    if (isEndConvertScore)
    {
        pressSpaceKeyUI->Draw();
        //前回のハイスコアより大きかったら
        if (resultScore->IsUpdateHiScore())
        {
            //ハイスコア更新の文字
            UIDrawer::DrawRotaUI(hiScoreUI);
        }
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
/// クリアタイムのスコア変換
/// </summary>
void PostGoalStaging::ConvertTimeScotre()
{
    if (!SoundPlayer::IsPlaySound(sceneNextSE))
    {
        //スコアを換算し終えたか、スペースキーを押したら終了
        if ((larpConvertScoreTimer->IsOverLimitTime() || clearTime < 0 || UserInput::GetInputState(Space) == Push))
        {
            //次の処理
            nowConvertScore = collectBonus;
                //タイムボーナスを表示したら終了
                SoundPlayer::StopSound(scoreStartSE);
                timeScoreUI.score = resultScore->GetScore(timeBonus);
                drawClearTime = 0.0000f;
        }
        //タイマーが動いている間はスコア換算
        else
        {
            //残り時間をスコアに換算
            float larpValue = static_cast<float>(larpConvertScoreTimer->GetElaspedTime() / scoreLarpTime);

            timeScoreUI.score = static_cast<int>(larpValue * resultScore->GetScore(timeBonus));
            //描画するクリアタイムを更新
            drawClearTime = clearTime - static_cast<float>(clearTime * larpValue);
            //スコア加算中はずっと鳴る
            if (!SoundPlayer::IsPlaySound(scoreStartSE))
            {
                SoundPlayer::Play2DSE(scoreStartSE);
            }
        }
    }
    //各スコアを合計
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// 収集アイテムのスコア変換
/// </summary>
void PostGoalStaging::ConvertCollectScotre()
{
    //一つ一つスコアに変換する工程をスキップ
    bool isSkip = UserInput::GetInputState(Space) == Push;
    //効果音が鳴り終わったタイミングで入手した宝石をスコアに変換する
    if (!SoundPlayer::IsPlaySound(scoreEndSE) || isSkip)
    {
        //描画したアイテムの数が獲得したアイテムの数と同じ以上にになったら
        if (isSkip || (drawCollectIconNum >= getCollectNum && !isEndConvertScore))
        {
            //描画するスコアなどを記録と統一
            collectScoreUI.score = resultScore->GetScore(collectBonus);
            drawCollectIconNum = getCollectNum;
            isEndConvertScore = true;
            ////花吹雪エフェクト開始
            confettiEffect = EffectManager::GetPlayEffect2D(confetti);
            SetPosPlayingEffekseer2DEffect(confettiEffect, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 5);
            //ファンファーレ効果音
            SoundPlayer::Play2DSE(gameEndFanfare);
        }
        else
        {        //収集アイテムを一個ずつ配置
            SoundPlayer::Play2DSE(scoreEndSE);
            drawCollectIconNum++;
            collectScoreUI.score = resultScore->GetScoreBonus(collectBonus) * drawCollectIconNum;
        }
    }
    //各スコアを合計
    totalScoreUI.score = collectScoreUI.score + timeScoreUI.score;
}
/// <summary>
/// ゲーム終了のアナウンスを流すプロセス
/// </summary>
void PostGoalStaging::EndAnnounceProcess()
{
    if (!isSoundClapSE)
    {
        SoundPlayer::Play2DSE(clap);
        isSoundClapSE = true;
    }
    //larp移動が終了したら
    if (larpMoveAnnounceTimer->IsOverLimitTime())
    {
        isEndFinishAnnounce = true;
        larpConvertScoreTimer = new Timer(scoreLarpTime);
        SoundPlayer::Play2DSE(sceneNextSE);
    }
    else//移動させる
    {
        float larpTime = static_cast<float>(larpMoveAnnounceTimer->GetElaspedTime() / finishAnounceTime);
        //総数移動距離
        float graphWidth = finishAnnounceData.width / finishAnnounceData.dataHandle.size() * finishAnnounceData.size;
        float moveBetween = (SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
        finishAnnounceData.x = static_cast<int>(SCREEN_WIDTH * UIDrawer::GetScreenRaito() - larpTime * (moveBetween));
    }
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
/// <summary>
/// 残り時間スコアの描画
/// </summary>
void PostGoalStaging::TimeScoreDraw() const
{
    //クリアタイムの描画
    UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
    clearTimeUI->Draw(drawClearTime);
}
/// <summary>
/// 収集アイテムスコアの描画
/// </summary>
void PostGoalStaging::CollectScoreDraw() const
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
}
