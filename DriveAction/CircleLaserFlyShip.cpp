#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"

/// <summary>
/// 円状に陣形を作った飛行船
/// </summary>
CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
    :LaserFlyShip(firstPos, setDestinationPos,ObjectInit::circleLaserShip)
{
    GenerateLaser();
}

void CircleLaserFlyShip::GenerateLaser()
{
    DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::littleRadLaser, sub);
}

void CircleLaserFlyShip::Update()
{
    objState = active;
}
