#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageDataPass.h"
//ステージの横幅
int FirstPositionGetter::stageWidth;
//ステージの縦幅
int FirstPositionGetter::stageLength;

FirstPositionGetter::FirstPositionGetter()
{
    //収集アイテムと敵の位置を保存
    auto fileLoader = new CSVFileLoader(LoadStageData(challengesListFilePass));
    challengeVec = fileLoader->GetLoadStringData();
    SAFE_DELETE(fileLoader);
    //ステージの横幅縦幅を設定
    stageWidth = atoi(LoadStageData(width).c_str());
    stageLength = atoi(LoadStageData(length).c_str());

    using enum FirstPositionDataKind;
    //各オブジェクトの初期位置
    positionDataPassMap.insert(std::make_pair(playerPosition, LoadStageData(playerPositionFilePass)));
    positionDataPassMap.insert(std::make_pair(rockPosition, LoadStageData(rockFilePass)));
}

FirstPositionGetter::~FirstPositionGetter()
{
}
/// <summary>
/// 初期位置を渡す
/// </summary>
/// <param name="dataKind"></param>
/// <returns></returns>
std::unordered_map<int, std::vector<VECTOR>> FirstPositionGetter::GetFirstPositionLoad(FirstPositionDataKind dataKind)
{
    using enum FirstPositionDataKind;
    std::unordered_map<int, std::vector<VECTOR>> map;
    switch (dataKind)
    {
    case playerPosition:
        CSVConvertPosition(&map,positionDataPassMap[playerPosition]);
        break;
    case rockPosition:
        CSVConvertPosition(&map,positionDataPassMap[rockPosition]);
        break;
    }
    return map;
}
/// <summary>
/// 収集アイテムと敵の位置データ
/// </summary>
/// <returns></returns>
std::vector<ChallengeData> FirstPositionGetter::GetChallengeData()
{
    std::vector<ChallengeData> challengeDataVec;//こっちに移す
    for (int i = 0; i < challengeVec.size(); i++)
    {
        auto fileLoader = new CSVFileLoader(challengeVec[i]);
        auto passData = fileLoader->GetLoadStringData();
        SAFE_DELETE(fileLoader);
        ChallengeData challengeData;
        CSVConvertPosition(&challengeData.collectPos,passData[collectPositionFilePass]);//収集アイテムの位置
        CSVConvertPosition(&challengeData.enemyPos,passData[enemyPositionFilePass]);//敵のアイテムの位置

        challengeDataVec.push_back(challengeData);
    }
    return challengeDataVec;
}
/// <summary>
/// CSVファイルから引数のmapのkeyの場所を変換
/// </summary>
/// <param name="map"></param>
/// <param name="fileName"></param>
void FirstPositionGetter::CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map, std::string fileName)
{
    CSVFileLoader* csv = new CSVFileLoader(fileName);
    std::vector<std::string> positionData;
    positionData = csv->GetLoadStringData();
    //列の数を数える
    int lineCount = csv->GetLineCount();

    //行の数を数える
    int sideLine = positionData.size() / lineCount;
    //セルの数だけ検索して初期位置をリスト化
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < sideLine; j++)
        {
            int num = std::atof(positionData[i * sideLine + j].c_str());
            //-1以外の数字が入力されていたらマップを更新
            if (num != -1)
            {
                VECTOR pos;
                pos.x = j * stageWidth / lineCount - stageWidth / 2;
                pos.z = i * stageLength / sideLine - stageLength / 2;
                (*map)[num].push_back(pos);
            }
        }
    }
    SAFE_DELETE(csv);
}