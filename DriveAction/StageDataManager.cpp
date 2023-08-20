#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
//ステージのファイルの名前
std::string StageDataManager::fileAddres = "-1";
//ステージのデータ
std::vector<std::string> StageDataManager::dataVector;
//全ステージのデータが入っている
const std::string StageDataManager::allStageAddresFile = "data/stageData/stageDataList.csv";

//ステージの横幅
int StageDataManager::stageWidth;
//ステージの縦幅
int StageDataManager::stageLength;
/// <summary>
/// 所得するステージの変更
/// </summary>
/// <param name="select">今選んでいるステージを教えてもらう</param>
void StageDataManager::ChangeStageData(StageSelect* const select)
{
    //空だったら読み込む
    if (dataVector.empty())
    {
        InitStageData();
    }
    //選んでいるステージのアドレスを保存
    fileAddres = dataVector[select->GetStageNum()];

    stageWidth = atof(GetStageData(InitStage::width).c_str());
    stageLength = atof(GetStageData(InitStage::length).c_str());
}
/// <summary>
/// ステージの数
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataVector.size();
}

/// <summary>
/// ステージの名前
/// </summary>
/// <returns></returns>
std::string StageDataManager::GetLoadeStageName()
{
    if (fileAddres == "-1")
    {
        InitStageData();
    }
    return fileAddres;
}
/// <summary>
/// 引数についての文字列を出す
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::string StageDataManager::GetStageData(StageData dataKind)
{
    //今選択中のステージの情報を所得
    auto fileLoader = new CSVFileLoader(GetLoadeStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //引数の情報を返す
    return setStageInitDataVec[dataKind];
}
/// <summary>
/// 遊ぶステージのスコアのボーダーラインを返す
/// </summary>
/// <returns></returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetStageData(stageScoreFilePass));
    auto scoreInfo = fileLoader->GetLoadStringData();
    ScoreBorder scoreBorder;
    scoreBorder.gold = atoi(scoreInfo[StageScore::goldScore].c_str());
    scoreBorder.silver = atoi(scoreInfo[StageScore::silverScore].c_str());
    scoreBorder.bronze = atoi(scoreInfo[StageScore::bronzeScore].c_str());
    scoreBorder.highScore = atoi(scoreInfo[StageScore::highScore].c_str());
    scoreBorder.second = atoi(scoreInfo[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreInfo[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// 遊んでいるステージのハイスコアを更新
/// </summary>
/// <param name="hiScore">遊んだステージで出たスコア</param>
void StageDataManager::SaveHiScore(int hiScore)
{
    ScoreBorder score= GetScoreBorder();
    //区切り文字
    std::string colon = ",";
    std::string borderString = std::to_string(score.gold) + colon + std::to_string(score.silver) + colon + std::to_string(score.bronze) + colon;
    std::string updateString;
    //ハイスコアの更新
    if (score.highScore < hiScore)
    {
        updateString = std::to_string(hiScore) + colon + std::to_string(score.highScore) + colon + std::to_string(score.second) + colon;
    }
    else if (score.second < hiScore)
    {
        updateString = std::to_string(score.highScore) + colon + std::to_string(hiScore) + colon + std::to_string(score.second) + colon;
    }
    else if (score.third < hiScore)
    {
        updateString = std::to_string(score.highScore) + colon + std::to_string(score.second) + colon + std::to_string(hiScore) + colon;
    }
    //スコア更新有りなら書き込む
    if(!updateString.empty())
    {
        std::ofstream writing_file;
        std::string filePass = GetStageData(stageScoreFilePass);
        // ファイルを開いて
        writing_file.open(filePass, std::ios::out);
        //スコアの更新
        writing_file << borderString + updateString << std::endl;
    }
}
/// <summary>
/// 初期化
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//全ステージのデータリストを読み取る
    dataVector = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataVector[0];//とりあえず先頭を渡す
}
