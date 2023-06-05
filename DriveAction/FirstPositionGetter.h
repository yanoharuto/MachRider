#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
namespace InitStage
{
    enum StageData
    {
        width,
        length,
        rockFilePass,
        challengesListFilePass,
        playerPositionFilePass
    };

    enum Challenge
    {
        collectPositionFilePass,
        enemyPositionFilePass
    };
    struct ChallengeData
    {
        std::unordered_map<int, std::vector<VECTOR>> collectPos;
        std::unordered_map<int, std::vector<VECTOR>> enemyPos;
    };
    enum class FirstPositionDataKind
    {
        playerPosition,
        rockPosition,
    };
}
using namespace InitStage;
/// <summary>
/// èâä˙à íuÇê›íËÇ∑ÇÈ
/// </summary>
class FirstPositionGetter
{
public:
    FirstPositionGetter();
    ~FirstPositionGetter();
    static std::unordered_map<int, std::vector<VECTOR>>GetFirstPositionLoad(FirstPositionDataKind dataKind);

    static std::vector<ChallengeData> GetChallengeData();
private:
    static void CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>& map,std::string fileName);
    static int stageWidth;
    static int stageLength;
    static std::vector<std::string> challengeList;
    static std::unordered_map<FirstPositionDataKind,std::string> positionDataPassMap;
    static bool fileLoadFlag;


};