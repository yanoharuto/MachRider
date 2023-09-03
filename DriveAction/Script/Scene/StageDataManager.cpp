#include "StageDataManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "CSVFileLoader.h"
#include "StageSelect.h"
#include "ReusableTimer.h"
#include "ResultScore.h"
#include "ScoreRecordWriter.h"
//ステージのファイルの名前
std::string StageDataManager::fileAddres = "-1";
//ステージのデータ
std::vector<std::string> StageDataManager::dataVector;
//全ステージのリストのパスが入ったファイルのパス
const std::string StageDataManager::allStageFilePath = "data/stageData/stageDataList.csv";
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
    fileAddres = dataVector[select->GetSelectStageNum()];

    stageWidth = atof(GetSelectStageData(InitStage::width).c_str());
    stageLength = atof(GetSelectStageData(InitStage::length).c_str());
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
std::string StageDataManager::GetSelectStageName()
{
    if (fileAddres == "-1")
    {
        InitStageData();
    }
    return fileAddres;
}
/// <summary>
/// 各ステージのデータを取ってくる
/// </summary>
/// <param name="dataKind">欲しいステージのデータの種類</param>
/// <returns>ステージの制限時間や縦幅横幅、初期位置の入ったファイルのパスなどが返ってくる</returns>
std::string StageDataManager::GetSelectStageData(StageData dataKind)
{
    //今選択中のステージの情報を所得
    auto fileLoader = new CSVFileLoader(GetSelectStageName());
    auto setStageInitDataVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //引数の情報を返す
    return setStageInitDataVec[dataKind];
}
/// <summary>
/// 遊ぶステージのスコアのボーダーラインを返す
/// </summary>
/// <returns>現在遊んでいるステージのスコアの線引きを纏めたもの</returns>
ScoreBorder StageDataManager::GetScoreBorder()
{
    auto fileLoader = new CSVFileLoader(GetSelectStageData(stageScoreFilePass));
    //ステージ情報文字列コンテナ
    auto scoreStrInfoVec = fileLoader->GetLoadStringData();
    //ステージのスコアの線引き
    ScoreBorder scoreBorder;
    scoreBorder.gold = atoi(scoreStrInfoVec[StageScore::goldScore].c_str());
    scoreBorder.silver = atoi(scoreStrInfoVec[StageScore::silverScore].c_str());
    scoreBorder.bronze = atoi(scoreStrInfoVec[StageScore::bronzeScore].c_str());
    scoreBorder.highScore = atoi(scoreStrInfoVec[StageScore::highScore].c_str());
    scoreBorder.second = atoi(scoreStrInfoVec[StageScore::secondScore].c_str());
    scoreBorder.third = atoi(scoreStrInfoVec[StageScore::thirdScore].c_str());
    return scoreBorder;
}
/// <summary>
/// 初期位置の文字列情報
/// </summary>
/// <param name="tag">欲しいオブジェクトの初期位置情報のタグ</param>
/// <returns>tagのオブジェクトが初期位置を決めるときに必要な文字列情報</returns>
std::vector<std::string> StageDataManager::GetPlaceStrData(Object::ObjectTag tag)
{
    ///今選択しているステージの初期位置の入ったファイルのパス
    std::string selectStageFirstPlaceFilePath;
    //各オブジェクトの初期位置のファイルまでのパスを所得
    switch (tag)
    {
    case Object::player:
        selectStageFirstPlaceFilePath = GetSelectStageData(playerPositionFilePass);
        break;
    case Object::collect:
        selectStageFirstPlaceFilePath = GetSelectStageData(collectFilePass);
        break;
    default:
        selectStageFirstPlaceFilePath = GetSelectStageData(enemyFilePass);
        break;
    }
    //初期化文字列リストを取ってくる
    CSVFileLoader* csv = new CSVFileLoader(selectStageFirstPlaceFilePath);
    return csv->GetLoadStringData();
}
/// <summary>
/// ゲームの制限時間のタイマーを作成
/// </summary>
/// <returns>ゲーム制限時間タイマー</returns>
ReusableTimer* StageDataManager::CreateGameTimer()
{
    float gameLimitTime = SAFE_STR_TO_F(GetSelectStageData(gameTime));
    return new ReusableTimer(gameLimitTime);
}
/// <summary>
/// スコアの記録更新役を渡す
/// </summary>
/// <returns>スコアの記録更新役</returns>
ScoreRecordWriter* StageDataManager::GetScoreRecordWriter()
{
    return new ScoreRecordWriter(GetSelectStageData(stageScoreFilePass),GetScoreBorder());
}
/// <summary>
/// 初期化
/// </summary>
void StageDataManager::InitStageData()
{
    auto fileLoader = new CSVFileLoader(allStageFilePath);//全ステージのデータリストを読み取る
    dataVector = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    fileAddres = dataVector[0];//とりあえず先頭を渡す
}
