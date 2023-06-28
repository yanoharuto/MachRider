#pragma once
#include "StageDataPass.h"

using namespace InitStage;
/// <summary>
/// 初期位置を設定する
/// </summary>
class FirstPositionGetter :StageDataPass
{
public:
    FirstPositionGetter();
    ~FirstPositionGetter();
    /// <summary>
    /// 初期位置を渡す
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::unordered_map<int, std::vector<VECTOR>>GetFirstPositionLoad(FirstPositionDataKind dataKind);
    /// <summary>
    /// 収集アイテムと敵の位置データ
    /// </summary>
    /// <returns></returns>
    std::vector<ChallengeData> GetChallengeData();
private:
    /// <summary>
    /// CSVファイルから引数のmapのkeyの場所を変換
    /// </summary>
    /// <param name="map"></param>
    /// <param name="fileName"></param>
    static void CSVConvertPosition(std::unordered_map<int, std::vector<VECTOR>>* map,std::string fileName);
    //幅
    static int stageWidth;
    //長さ
    static int stageLength;
    //プレイヤーがこなさなければいけない課題のVector
    std::vector<std::string> challengeVec;
    //プレイヤーかステージのオブジェクトの配置
    std::unordered_map<FirstPositionDataKind,std::string> positionDataPassMap;
};