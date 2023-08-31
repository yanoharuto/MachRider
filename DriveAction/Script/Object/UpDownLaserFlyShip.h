#pragma once
#include "LaserFlyShip.h"
#include "EditObjectData.h"
/// <summary>
/// 上下に動きながらレーザーを出すやつ
/// </summary>
class UpDownLaserFlyShip : public LaserFlyShip
{
public:
    /// <summary>
    /// 上下に動きながらレーザーを出すやつ
    /// </summary>
    UpDownLaserFlyShip(PlacementData setPos);
    /// <summary>
    /// 上下に動くよ
    /// </summary>
    void Update() override;
private:
    //totalMoveValueの増加量
    static const float addMoveValue;
    //上下に動く速度
    static const float updownSpeed;
    //動いた量
    float totalMoveValue = 0;
};

