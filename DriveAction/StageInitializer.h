#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include "DxLib.h"
class ActorControllerManager;
class ObjectObserver;

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
/// <summary>
/// ステージの初期化
/// </summary>
class StageInitializer
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageInitializer();
    ~StageInitializer();
    void Init(ActorControllerManager* cotrollerManager);
    std::shared_ptr<ObjectObserver> GetPlayerObserver()const;
    float GetGameTime()const;
private:
    std::shared_ptr<ObjectObserver> playerObserver;
};