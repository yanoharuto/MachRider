#pragma once
#include "Actor.h"
#include "FlyShipController.h"
#include "EditObjectData.h"
#include <string>
class Timer;
class ReusableTimer;
class DamageObjGenerator;
/// <summary>
/// 爆撃機
/// </summary>
class BomberFlyShip : public Actor
{
public:
    /// <summary>
    /// 引数の位置に生成　
    /// </summary>
    /// <param name="data">生成位置と向きが入った構造体</param>
    /// <param name="initParam">爆弾発射クールタイムを所得</param>
    /// <param name="damageObjGenerator">爆弾発射に必要なクラス</param>
    BomberFlyShip(PlacementData data,FlyShipInit::InitFlyShipParamator initParam,std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// damageObjectGeneratorの開放
    /// </summary>
    ~BomberFlyShip();
    /// <summary>
    /// 爆弾を落としながら進む
    /// </summary>
    void Update() override;
private:
    //爆弾を落とす時間
    ReusableTimer* bombFallTimer;
    //爆弾を生成するのに必要なクラス
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};

