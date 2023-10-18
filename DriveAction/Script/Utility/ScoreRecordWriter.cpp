#include "ScoreRecordWriter.h"
#include "ResultScore.h"
#include <rapidjson.h>
#include <document.h>
#include <ostreamwrapper.h>
#include <writer.h>

/// <summary>
/// スコアの記録を所得
/// </summary>
/// <param name="filePath">スコアのファイルのパス</param>
/// <param name="scoreBorder">そのステージのスコアの記録の線引き</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, StageDataManager::ScoreBorder scoreBorder)
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
    //ドキュメント作成
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();    //jsonに書き込む準備
    jsonDoc.AddMember("gold", border.gold, allocator);
    jsonDoc.AddMember("silver", border.silver, allocator); 
    jsonDoc.AddMember("bronze", border.bronze, allocator);
    //ハイスコアランキング1位の更新
    if (border.highScore < highScore)
    {
        updateString = highScoreStr + colon + std::to_string(border.highScore) + colon + std::to_string(border.second) + colon;
        jsonDoc.AddMember("firstScore", highScore, allocator);
        jsonDoc.AddMember("secondScore", border.second, allocator);
        jsonDoc.AddMember("thirdScore", border.third, allocator);

    }
    //2位の更新
    else if (border.second < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + highScoreStr + colon + std::to_string(border.second) + colon;
        jsonDoc.AddMember("firstScore", border.highScore, allocator);
        jsonDoc.AddMember("secondScore", highScore, allocator);
        jsonDoc.AddMember("thirdScore", border.third, allocator);
    }
    //3位の更新
    else if (border.third < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + std::to_string(border.second) + colon + highScoreStr + colon; 
        jsonDoc.AddMember("firstScore", border.highScore, allocator);
        jsonDoc.AddMember("secondScore", border.second, allocator);
        jsonDoc.AddMember("thirdScore", highScore, allocator);
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
        //ファイルの中身を全部消した状態で書き込む
        std::ofstream ofs(scoreRecordFilePath,std::ios::out);
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        jsonDoc.Accept(writer);
    }
}