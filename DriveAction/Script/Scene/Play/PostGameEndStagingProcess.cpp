#include "PostGameEndStagingProcess.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "GameScreen.h"
#include "SpaceKeyUI.h"
#include "NumUI.h"
#include "Timer.h"
#include "GameScreen.h"
#include "PlayerObserver.h"
#include "Object.h"
#include "UIDrawer.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "ScoreNum.h"
#include "PlayerObserver.h"
/// <summary>
/// ゴール後の演出をする
/// </summary>
/// <param name="player">ResultScoreにプレイヤー情報を渡す</param>
/// <param name="gameTimer">クリアタイムを受け取る</param>
PostGameEndStagingProcess::PostGameEndStagingProcess(std::weak_ptr<PlayerObserver> player, std::shared_ptr<Timer> gameTimer)
{
    //スコアを確定
    resultScore = new ResultScore(player,gameTimer);
    //音を所得
    using enum SoundKind;
    using enum UIKind;
    SoundPlayer::StopAllSound();
    SoundPlayer::LoadAndInitSound(clap);
    SoundPlayer::LoadAndInitSound(scoreEndSE);
    SoundPlayer::LoadAndInitSound(scoreStartSE);
    SoundPlayer::LoadAndInitSound(sceneNextSE);
    SoundPlayer::LoadAndInitSound(gameEndFanfare);
    
    //プレイヤーの所得した収集アイテム
    getCollectNum = player.lock()->GetCollectCount();
    drawCollectIconNum = 0;
    //最初の処理
    nowConvertScore = timeBonus;
    //タイムボーナス
    timeScoreUI = GetScoreUI(timeScore);
    
    //収集アイテムボーナス
    collectScoreUI = GetScoreUI(collectScore);
    collectUIData = UIManager::CreateUIData(collectScoreIcon);
    //合計スコア
    totalScoreUI = GetScoreUI(totalScore);
    totalScoreNumUI = new ScoreNum();
    //ハイスコア更新UI
    highScoreUIData = UIManager::CreateUIData(PraiseWord);
    //ゲーム終了時画面
    gameEndScreen = GameScreen::GetScreen();
    //スペースキー催促
    pressSpaceKeyUI = new FlashUI(resultSpaceKey);
    //クリアタイム保存
    clearTime = static_cast<float>(gameTimer->GetRemainingTime());
    drawClearTime = clearTime;
    clearTimeUI = new NumUI(timeScoreNum);
    //ゲーム終了アナウンス
    finishAnnounceUIData = UIManager::CreateUIData(finishAnnounce);
    finishAnnounceUIData.x = SCREEN_WIDTH;
    larpMoveAnnounceTimer = new Timer(finishAnounceTime);
    //花吹雪
    EffectManager::LoadEffect(EffectKind::confetti);
}
/// <summary>
/// 各UIを削除する
/// </summary>
PostGameEndStagingProcess::~PostGameEndStagingProcess()
{
    SAFE_DELETE(larpConvertScoreTimer);
    SAFE_DELETE(clearTimeUI);
    SAFE_DELETE(pressSpaceKeyUI);
    SAFE_DELETE(larpMoveAnnounceTimer);
    SAFE_DELETE(totalScoreNumUI);
    SAFE_DELETE(resultScore);
    UIManager::DeleteUIGraph(&highScoreUIData);
    UIManager::DeleteUIGraph(&finishAnnounceUIData);
    UIManager::DeleteUIGraph(&collectUIData);
    StopEffekseer2DEffect(confettiEffect);
}
/// <summary>
/// スコアの数字を徐々に出していく処理
/// </summary>
/// <returns></returns>
void PostGameEndStagingProcess::Update()
{
    if (!isEndFinishAnnounce)//終了アナウンスを出す
    {
        EndAnnounceProcess();
    }
    else if (isEndConvertScore)//加算処理終了後は加算音を消す
    {
        SoundPlayer::StopSound(SoundKind::scoreEndSE);

        pressSpaceKeyUI->Update();
        //スペースキーを押して終了
        if (UserInput::GetInputState(Space) == Push)
        {
            SoundPlayer::Play2DSE(SoundKind::sceneNextSE);
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
void PostGameEndStagingProcess::Draw()const
{
    //ゲーム終了時の画面を暗く表示
    SetDrawBright(backScreenBright, backScreenBright, backScreenBright);
    DrawGraph(0, 0, gameEndScreen, false);
    SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);

    //終了アナウンス
    if (!isEndFinishAnnounce) 
    {
        int safeNum = static_cast<int>(larpMoveAnnounceTimer->GetElaspedTime()) % finishAnnounceUIData.dataHandle.size();
        UIDrawer::DrawRotaUI(finishAnnounceUIData,safeNum);
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
            UIDrawer::DrawRotaUI(highScoreUIData);
        }
    }
}
/// <summary>
/// 処理を終了したか
/// </summary>
/// <returns></returns>
bool PostGameEndStagingProcess::IsEndProcess() const
{
    return isEndProcess;
}
/// <summary>
/// クリアタイムのスコア変換
/// </summary>
void PostGameEndStagingProcess::ConvertTimeScotre()
{
    using enum SoundKind;
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
void PostGameEndStagingProcess::ConvertCollectScotre()
{
    using enum SoundKind;
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
            confettiEffect = EffectManager::GetPlayEffect2D(EffectKind::confetti);
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
void PostGameEndStagingProcess::EndAnnounceProcess()
{
    using enum SoundKind;
    //最初の一回だけ拍手する
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
        float graphWidth = finishAnnounceUIData.width / finishAnnounceUIData.dataHandle.size() * finishAnnounceUIData.size;
        float moveBetween = (SCREEN_WIDTH + graphWidth) * UIDrawer::GetScreenRaito();
        finishAnnounceUIData.x = static_cast<int>(SCREEN_WIDTH * UIDrawer::GetScreenRaito() - larpTime * (moveBetween));
    }
}
/// <summary>
/// スコアに関するUIを所得
/// </summary>
/// <param name="kind"></param>
/// <returns></returns>
ScoreUI PostGameEndStagingProcess::GetScoreUI(UIKind kind)
{
    ScoreUI ui;
    ui.scoreKindData = UIManager::CreateUIData(kind);
    ui.score = 0;
    return ui;
}
/// <summary>
/// 残り時間スコアの描画
/// </summary>
void PostGameEndStagingProcess::TimeScoreDraw() const
{
    //クリアタイムの描画
    UIDrawer::DrawRotaUI(timeScoreUI.scoreKindData);
    clearTimeUI->Draw(drawClearTime);
}
/// <summary>
/// 収集アイテムスコアの描画
/// </summary>
void PostGameEndStagingProcess::CollectScoreDraw() const
{
    //収集アイテムスコアのUI
    UIDrawer::DrawRotaUI(collectScoreUI.scoreKindData);
    //所得したアイテムを少しずつ描画
    for (int i = 1; i <= drawCollectIconNum; i++)
    {
        UIData icon = collectUIData;
        icon.x += static_cast<int>(collectUIData.width * UIDrawer::GetScreenRaito() * icon.size * i);//右にずらしていく
        UIDrawer::DrawRotaUI(icon);
    }
}
