#include "ScoreRecordWriter.h"
#include "ResultScore.h"
/// <summary>
/// スコアの記録を所得
/// </summary>
/// <param name="filePath">スコアのファイルのパス</param>
/// <param name="scoreBorder">そのステージのスコアの記録の線引き</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, InitStage::ScoreBorder scoreBorder)
{
    //CSVファイルの区切り文字
    std::string colon = ",";
    scoreRecordFilePath = filePath;
    border = scoreBorder;
    //変更しない線引きの箇所
    borderString = std::to_string(scoreBorder.gold) + colon + std::to_string(scoreBorder.silver) + colon + std::to_string(scoreBorder.bronze) + colon;
}
/// <summary>
/// スコアの記録の更新
/// </summary>
/// <param name="score">現在遊んでいるステージの記録を教えてもらう</param>
void ScoreRecordWriter::UpdateScoreRecord(ResultScore* const resultScore)
{
    //最高スコア
    int highScore = resultScore->GetUpdateScore();
    //CSVファイルの区切り文字
    std::string colon = ",";
    //スコアのランキング文字列
    std::string updateString;
    //ハイスコアの文字列
    std::string highScoreStr = std::to_string(highScore);
    //ハイスコアランキング1位の更新
    if (border.highScore < highScore)
    {
        updateString = highScoreStr + colon + std::to_string(border.highScore) + colon + std::to_string(border.second) + colon;
    }
    //2位の更新
    else if (border.second < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + highScoreStr + colon + std::to_string(border.second) + colon;
    }
    //3位の更新
    else if (border.third < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + std::to_string(border.second) + colon + highScoreStr + colon;
    }
    //スコア更新有りなら書き込む
    if (!updateString.empty())
    {
        // ファイルを開いて
        std::ofstream writing_file;
        writing_file.open(scoreRecordFilePath, std::ios::out);
        //スコアの更新
        writing_file << borderString + updateString << std::endl;
        //書き込み終了
        writing_file.close();
    }
}