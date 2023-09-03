#include "ScoreRecordWriter.h"
#include "ResultScore.h"
/// <summary>
/// 更新するスコアのファイルを開く
/// </summary>
/// <param name="filePath">スコアのファイルのパス</param>
/// <param name="scoreBorder">そのステージのスコアの記録の線引き</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, InitStage::ScoreBorder scoreBorder)
{
    border = scoreBorder;
    // ファイルを開いて
    writing_file.open(filePath, std::ios::out);
}
/// <summary>
/// スコアの記録の更新
/// </summary>
/// <param name="score">現在遊んでいるステージの記録を教えてもらう</param>
void ScoreRecordWriter::UpdateScoreRecord(ResultScore* const resultScore)
{
    //区切り文字
    std::string colon = ",";
    //スコアの線引き文字列
    std::string borderString = std::to_string(border.gold) + colon + std::to_string(border.silver) + colon + std::to_string(border.bronze) + colon;
    //スコアのランキング文字列
    std::string updateString;
    std::string highScoreStr = resultScore->GetHighScoreString();
    int highScore = atoi(highScoreStr.c_str());
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
        //スコアの更新
        writing_file << borderString + updateString << std::endl;
    }
}
