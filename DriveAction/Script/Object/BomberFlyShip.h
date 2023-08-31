#pragma once
#include "Actor.h"
#include "FlyShipController.h"
#include "EditObjectData.h"
#include <string>
class Timer;
class ReusableTimer;
/// <summary>
/// 爆撃機
/// </summary>
class BomberFlyShip : public Actor
{
public:
    /// <summary>
    /// 爆撃機
    /// </summary>
    /// <param name="setFirstPos">出現位置</param>
    /// <param name="setDestinationPos">目的地</param>
    BomberFlyShip(PlacementData data,FlyShipInit::InitFlyShipParamator initParam);
    /// <summary>
    /// 爆弾を落としながら進む
    /// </summary>
    void Update() override;
private:
    //爆弾を落とす時間
    ReusableTimer* bombFallTimer;
};

