#include "UpDownLaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include <math.h>
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
const float UpDownLaserFlyShip::updownSpeed = 6.0f;

UpDownLaserFlyShip::UpDownLaserFlyShip(VECTOR setPos)
    :LaserFlyShip(setPos,VGet(0,setPos.y,0), ObjectInit::upDownLaserShip)
{
    GenerateLaser();
}

void UpDownLaserFlyShip::Update()
{
    objState = active;
    totalMoveValue += addMoveValue;
    position.y += cosf(totalMoveValue) * updownSpeed;
    ReflectsVelocity();
}

void UpDownLaserFlyShip::GenerateLaser()
{
    DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::bigRadLaser, sub);
}
