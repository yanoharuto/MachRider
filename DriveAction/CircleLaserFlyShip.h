#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// 円状に陣形を組みレーザーを発射する飛行船
/// </summary>
class CircleLaserFlyShip :
    public LaserFlyShip
{
public:
    /// <summary>
    /// 円状に陣形を組みレーザーを発射する飛行船
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// レーザーを発射する
    /// </summary>
    void GenerateLaser() override;
private:
};

