#include <fstream>
#include <sstream>
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
    ScoreBorder score = StageDataManager::GetScoreBorder();
    //制限時間を超過してたら0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetRemainingTime() * clearTimeBonus);
    //収集アイテムを取ってたらボーナス
    collectScore= player.lock()->GetCollectCount() * getCollectBonus;
    //得点
    int highScore = timeScore + collectScore;
    //↑二つが過去のハイスコアより多かったらTrue
    isUpdateHighScore = timeScore + collectScore > score.highScore;
    //ハイスコア更新ならデータを書き換える
    if(isUpdateHighScore)
    {
        //区切り文字
        std::string colon = ",";
        //スコアの線引き文字列
        std::string borderString = std::to_string(score.gold) + colon + std::to_string(score.silver) + colon + std::to_string(score.bronze) + colon;
        //スコアのランキング文字列
        std::string updateString;
        //ハイスコアランキング1位の更新
        if (score.highScore < highScore)
        {
            updateString = std::to_string(highScore) + colon + std::to_string(score.highScore) + colon + std::to_string(score.second) + colon;
        }
        //2位の更新
        else if (score.second < highScore)
        {
            updateString = std::to_string(score.highScore) + colon + std::to_string(highScore) + colon + std::to_string(score.second) + colon;
        }
        //3位の更新
        else if (score.third < highScore)
        {
            updateString = std::to_string(score.highScore) + colon + std::to_string(score.second) + colon + std::to_string(highScore) + colon;
        }
        //スコア更新有りなら書き込む
        if (!updateString.empty())
        {
            std::ofstream writing_file;
            //ステージのスコアをまとめたファイルのパス
            std::string filePass = StageDataManager::GetSelectStageData(stageScoreFilePass);
            // ファイルを開いて
            writing_file.open(filePass, std::ios::out);
            //スコアの更新
            writing_file << borderString + updateString << std::endl;
        }
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
