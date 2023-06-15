#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "DxLib.h"
#include "StageInitializer.h"
using namespace InitStage;
/// <summary>
/// 初期位置を設定する
/// </summary>
class FirstPositionGetter
{
public:
    FirstPositionGetter();
    ~FirstPositionGetter();
    /// <summary>
    /// 初期位置をロード
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::unordered_map<int, std::vector<VECTOR>>GetFirstPositionLoad(FirstPositionDataKind dataKind);
    std::vector<ChallengeData> GetChallengeData();
private:
    static void CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map,std::string fileName);
    static int stageWidth;
    static int stageLength;
    //プレイヤーがこなさなければいけない課題のVector
    std::vector<std::string> challengeVec;
    //プレイヤーかステージのオブジェクトの配置
    std::unordered_map<FirstPositionDataKind,std::string> positionDataPassMap;
};