#include <iostream>
#include <memory>
#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
/// <summary>
/// ���[�U�[�𔭎˂����s�D
/// </summary>
LaserFlyShip::LaserFlyShip(ObjectInit::InitObjKind kind)
    :Actor(kind)
{
    firstPosY = position.y;
}
/// <summary>
/// ���[�U�[���쐬
/// </summary>
/// <param name="kind"></param>
void LaserFlyShip::GenerateLaser(DamageObjectGenerator::DamageObjectKind kind)
{
    DamageObjectGenerator::GenerateDamageObject(kind,std::make_unique<ObjectObserver>(this));
}