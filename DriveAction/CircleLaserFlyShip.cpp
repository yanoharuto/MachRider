#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"

/// <summary>
/// ‰~ó‚ÉwŒ`‚ğì‚Á‚½”òs‘D
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
/// •`‰æ‚Å‚«‚é’iŠK‚É‚È‚Á‚½‚çactive‚É‚È‚é
/// </summary>
void CircleLaserFlyShip::Update()
{
    objState = active;
}
