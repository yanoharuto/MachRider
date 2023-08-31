#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// 円状に陣形を組みレーザーを発射する飛行船
/// </summary>
class CircleLaserFlyShip : public LaserFlyShip
{
public:
    /// <summary>
    /// 円状に陣形を組みレーザーを発射する飛行船
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// 描画できる段階になったらactiveになる
    /// </summary>
    void Update()override;
private:
};

