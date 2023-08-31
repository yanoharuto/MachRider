#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"

/// <summary>
/// �~��ɐw�`���������s�D
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
/// �`��ł���i�K�ɂȂ�����active�ɂȂ�
/// </summary>
void CircleLaserFlyShip::Update()
{
    objState = active;
}
