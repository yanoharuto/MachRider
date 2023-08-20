#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "PlayerObserver.h"
#include "StageDataManager.h"
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
    //制限時間を超過してたら0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetRemainingTime() * clearTimeBonus);
    //収集アイテムを取ってたらボーナス
    collectScore= player.lock()->GetCollectCount() * getCollectBonus;
    //↑二つが過去のハイスコアより多かったらTrue
    isUpdateHiScore = timeScore + collectScore > StageDataManager::GetScoreBorder().highScore;
    //スコアの更新
    StageDataManager::SaveHiScore(timeScore + collectScore);
}
/// <summary>
/// ハイスコアが更新されたか
/// </summary>
/// <returns>ハイスコアが更新されていたらTrue</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHiScore;
}
