#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DxLib.h"
namespace InitStage
{
    enum StageData
    {
        width = 1,
        length = 3,
        rockFilePass = 5,
        challengesListFilePass = 7,
        playerPositionFilePass = 9,
        gameTime = 11,
        stageScoreFilePass = 13
    };
    enum StageScore
    {
        firstScore,
        secondScore,
        thirdScore
    };
    enum Challenge
    {
        collectPositionFilePass = 1,
        enemyPositionFilePass = 3
    };
    /// <summary>
    /// プレイヤーがこなす内容　
    /// 集めるアイテムの位置と敵の位置を保存している
    /// </summary>
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
/// 遊ぶステージのデータのパスを渡す
/// </summary>
class StageDataPass
{
public:
    StageDataPass();
    virtual ~StageDataPass();
 
protected:
    /// <summary>
    /// どのステージを選んでいるか
    /// </summary>
    /// <returns></returns>
    std::string GetLoadeStageName()const;
    /// <summary>
    /// 各ステージのデータを取ってくる
    /// </summary>
    /// <param name="dataKind"></param>
    /// <returns></returns>
    std::string LoadStageData(StageData dataKind)const;
    //ステージの一覧的な奴
    const std::string allStageAddresFile = "data/stageData/stageDataList.csv";
    //ステージのパスを読み取る
    std::vector<std::string> dataLoader;
    //各ステージのデータのパス
    static std::string fileAddres;
};