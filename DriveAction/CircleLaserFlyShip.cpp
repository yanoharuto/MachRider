#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"

/// <summary>
/// 円状に陣形を作った飛行船
/// </summary>
CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
    :LaserFlyShip(ObjectInit::circleLaserShip)
{
    position.x = firstPos.x;
    position.z = firstPos.z;
    setDestinationPos.y = position.y;
    direction = VNorm(VSub(setDestinationPos, position));
    GenerateLaser(DamageObjectGenerator::littleRadLaser);
}

/// <summary>
/// 描画できる段階になったらactiveになる
/// </summary>
void CircleLaserFlyShip::Update()
{
    objState = active;
}
