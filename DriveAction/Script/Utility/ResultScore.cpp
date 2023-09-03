#include <fstream>
#include <sstream>
#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "PlayerObserver.h"
#include "StageDataManager.h"
#include "ScoreRecordWriter.h"
//収集アイテムゲットボーナス
const int ResultScore::getCollectBonus = 500;
//残り時間のボーナス
const int ResultScore::clearTimeBonus = 50;
/// <summary>
/// ゲームクリアしたときのスコアを計算する
/// </summary>
/// <param name="timer">クリアタイム</param>
/// <param name="player">クリアしたプレイヤーの情報通達役</param>
ResultScore::ResultScore(Timer* timer, std::weak_ptr<PlayerObserver> player)
{
    FixScore(timer, player);
}

/// <summary>
/// スコア所得
/// </summary>
/// <param name="scoreKind">欲しいスコアの種類</param>
/// <returns>引数のスコア量</returns>
int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ResultScore::timeBonus:
        return timeScore;
        break;
    case ResultScore::collectBonus:
        return collectScore;
        break;
    case ResultScore::total:
        return timeScore + collectScore;
        break;
    }
}
/// <summary>
/// スコアの倍率を所得
/// </summary>
/// <param name="scoreKind">欲しいスコアの種類</param>
/// <returns>引数のスコアの倍率</returns>
int ResultScore::GetScoreBonus(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ResultScore::timeBonus:
        return clearTimeBonus;
        break;
    case ResultScore::collectBonus:
        return getCollectBonus;
        break;
    default:
        return -1;
        break;
    }
}
/// <summary>
/// スコアを確定させる
/// </summary>
/// <param name="timer">クリアタイム所得</param>
/// <param name="player">プレイヤーの所得した収集アイテムを調べる</param>
void ResultScore::FixScore(Timer* const timer, std::weak_ptr<PlayerObserver> player)
{
    ScoreBorder score = StageDataManager::GetScoreBorder();
    //制限時間を超過してたら0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetRemainingTime() * clearTimeBonus);
    //収集アイテムを取ってたらボーナス
    collectScore= player.lock()->GetCollectCount() * getCollectBonus;
    //得点
    int highScore = timeScore + collectScore;
    //↑二つが過去のハイスコアより多かったらTrue
    isUpdateHighScore = timeScore + collectScore > score.highScore;
    //スコアが更新されたなら
    if(isUpdateHighScore)
    {
        updateStr = highScore;
        ScoreRecordWriter* scoreRecordWriter = StageDataManager::GetScoreRecordWriter();
        scoreRecordWriter->UpdateScoreRecord(this);
    }
}
/// <summary>
/// ハイスコアが更新されたか
/// </summary>
/// <returns>ハイスコアが更新されていたらTrue</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHighScore;
}
/// <summary>
/// ステージのハイスコアを文字列にしたもの
/// </summary>
/// <returns>ステージのハイスコアを文字列にしたもの</returns>
std::string ResultScore::GetHighScoreString() const
{
    return updateStr;
}
