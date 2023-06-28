#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "InitActor.h"
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
class ActorController;
class ActorControllerManager;
using namespace ObjectInit;
/// <summary>
/// 敵機のマネージャー
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
/// 敵機の初期化する
/// </summary>
    EnemyGenerator();

    ~EnemyGenerator() {};

    void GetActorControllerVector(ActorControllerManager* controllerManager);
    
private:
    void CreateActorController(InitObjKind kind, std::unordered_map<int, std::vector<VECTOR>> generatePosMap, ActorControllerManager* controllerManager);
    //ステージに配置されるアイテムの最大数
    int totalCollectNum = 0;
    //何番目の収集アイテムか
    int collectNum = -1;
    //敵の位置まとめ
    std::vector<InitStage::ChallengeData> challengeDataVec;
};