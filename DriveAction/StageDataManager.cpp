#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
//
std::string StageDataManager::fileAddres = "-1";
//
std::vector<std::string> StageDataManager::dataLoader;
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
    if (dataLoader.empty())
    {
        InitStageData();
    }
    //選んでいるステージのアドレスを保存
    fileAddres = dataLoader[select->GetStageNum()];

    stageWidth = atof(GetStageData(InitStage::width).c_str());
    stageLength = atof(GetStageData(InitStage::length).c_str());
}
/// <summary>
/// ステージの数
/// </summary>
/// <returns></returns>
int StageDataManager::GetStageTotalNumber()
{
    return dataLoader.size();
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
/// スコアのボーダーラインを返す
/// </summary>
/// <returns></returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetStageData(stageScoreFilePass));
    auto scoreInfo = fileLoader->GetLoadStringData();
    ScoreBorder scoreBorder;
    scoreBorder.first = atoi(scoreInfo[StageScore::firstScore].c_str());
    scoreBorder.second = atoi(scoreInfo[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreInfo[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// 初期化
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageAddresFile);//全ステージのデータリストを読み取る
    dataLoader = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataLoader[0];//とりあえず先頭を渡す
}
