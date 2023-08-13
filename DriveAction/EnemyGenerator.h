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
/// 敵機の生成を行う
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
    /// 敵機位置についての初期化する
    /// </summary>
    EnemyGenerator();

    ~EnemyGenerator() {};
    /// <summary>
    /// エネミーを生成
    /// </summary>
    /// <param name="collectNum">今プレイヤーは何個目の収集アイテムを取ったか</param>
    void GenerateEnemys(int collectNum,ActorController* const addObjController);
private:
    /// <summary>
    /// エネミーの配置情報を所得
    /// </summary>
    /// <param name="kind">どの種類か</param>
    /// <param name="collectNum">何番目の収集アイテムの時か</param>
    /// <returns>kindのエネミーの配置情報</returns>
    std::vector<EditArrangementData> GetNowEnemyEditData(int collectNum);
    
    //敵の位置まとめ
    std::vector<EditArrangementData> editDataVec;
};