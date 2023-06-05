#include "FirstPositionGetter.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageManager.h"
#include "StageSelect.h"
bool FirstPositionGetter::fileLoadFlag = false;
int FirstPositionGetter::stageWidth;
int FirstPositionGetter::stageLength;
std::vector<std::string> FirstPositionGetter::challengeList;
std::unordered_map<FirstPositionDataKind, std::string> FirstPositionGetter::positionDataPassMap;
FirstPositionGetter::FirstPositionGetter()
{
    if (fileLoadFlag == false)
    {
        auto fileLoader = new CSVFileLoader(StageSelect::GetLoadeStageName());
        auto setStageInitDataVec = fileLoader->GetLoadStringData();
        SAFE_DELETE(fileLoader);
        fileLoader = new CSVFileLoader(setStageInitDataVec[challengesListFilePass]);
        challengeList = fileLoader->GetLoadStringData();
        SAFE_DELETE(fileLoader);

        stageWidth = atoi(setStageInitDataVec[width].c_str());
        stageLength = atoi(setStageInitDataVec[length].c_str());
        using enum FirstPositionDataKind;
        positionDataPassMap.insert(std::make_pair(playerPosition, setStageInitDataVec[playerPositionFilePass]));
        positionDataPassMap.insert(std::make_pair(rockPosition, setStageInitDataVec[rockFilePass]));
        fileLoadFlag = true;
    }
}

FirstPositionGetter::~FirstPositionGetter()
{
}

std::unordered_map<int, std::vector<VECTOR>> FirstPositionGetter::GetFirstPositionLoad(FirstPositionDataKind dataKind)
{
    using enum FirstPositionDataKind;
    std::unordered_map<int, std::vector<VECTOR>> map;
    switch (dataKind)
    {
    case playerPosition:
        CSVConvertPosition(map,positionDataPassMap[playerPosition]);
        break;
    case rockPosition:
        CSVConvertPosition(map,positionDataPassMap[rockPosition]);
        break;
    }
    return map;
}

std::vector<ChallengeData> FirstPositionGetter::GetChallengeData()
{
    std::vector<ChallengeData> challengeDataVec;
    for (int i = 0; i < challengeList.size(); i++)
    {
        auto fileLoader = new CSVFileLoader(StageSelect::GetLoadeStageName());
        auto passData = fileLoader->GetLoadStringData();
        SAFE_DELETE(fileLoader);
        ChallengeData challengeData;
        CSVConvertPosition(challengeData.collectPos,passData[collectPositionFilePass]);
        CSVConvertPosition(challengeData.enemyPos,passData[enemyPositionFilePass]);

        challengeDataVec.push_back(challengeData);
    }
    return challengeDataVec;
}

void FirstPositionGetter::CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>& map, std::string fileName)
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
                map[num].push_back(pos);
            }
        }
    }
    SAFE_DELETE(csv);

}

