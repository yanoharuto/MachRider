#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// 上下に動きながらレーザーを出すやつ
/// </summary>
class UpDownLaserFlyShip :
    public LaserFlyShip
{
public:
    /// <summary>
    /// 上下に動きながらレーザーを出すやつ
    /// </summary>
    UpDownLaserFlyShip(VECTOR setPos);
    /// <summary>
    /// 上下に動くよ
    /// </summary>
    void Update() override;
    /// <summary>
    /// レーザーを発射
    /// </summary>
    void GenerateLaser()override;
private:
    //Cosの量
    static const float addMoveValue;
    //上下に動く速度
    static const float updownSpeed;
    //動いた量
    float totalMoveValue = 0;
};

