#include <iostream>
#include <memory>
#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
#include "Utility.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
/// <summary>
/// レーザーを発射する飛行船
/// </summary>
LaserFlyShip::LaserFlyShip(ObjectInit::InitObjKind kind)
    :Actor(kind)
{
    firstPosY = position.y;
}
/// <summary>
/// レーザーを作成
/// </summary>
/// <param name="kind"></param>
void LaserFlyShip::GenerateLaser(DamageObjectGenerator::DamageObjectKind kind)
{
    DamageObjectGenerator::GenerateDamageObject(kind,std::make_unique<ObjectObserver>(this));
}