#pragma once
#include "FlyShip.h"
#include "FlyShipCommander.h"
#include <string>
class Timer;
class ReusableTimer;
/// <summary>
/// 爆撃機
/// </summary>
class BomberFlyShip :
    public FlyShip
{
public:
    /// <summary>
    /// 爆撃機
    /// </summary>
    /// <param name="setFirstPos">出現位置</param>
    /// <param name="setDestinationPos">目的地</param>
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos,FlyShipInit::InitFlyShipParamator initParam);
    /// <summary>
    /// 爆弾を落としながら進む
    /// </summary>
    void Update() override;
private:
    //爆弾を落とす時間
    ReusableTimer* bombFallTimer;
    //生存時間
    Timer* aliveTimer;
    //速さ
    static float speed;
};

