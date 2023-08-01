#pragma once
#include <vector>
#include <unordered_map>
#include "InitActor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class UpDownFlyShipController;
class CircleFlyShipController;
class BomberFlyShipController;
class SawController;
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
    EnemyGenerator(ActorControllerManager* controllerManager);

    ~EnemyGenerator() {};
    
    void GenerateEnemys(int collectNum);
private:
    std::vector<EditArrangementData> GetNowEnemyEditData(InitObjKind kind, int collectNum);
    
    //敵の位置まとめ
    std::vector<EditArrangementData> editDataVec;
    std::unordered_map<InitObjKind,ActorController*> enemyMap;
};