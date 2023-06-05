#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
#include "Utility.h"
#include "OriginalMath.h"
/// <summary>
/// レーザーを発射する飛行船
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDestinationPos"></param>
LaserFlyShip::LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos,ObjectInit::InitObjKind kind)
    :FlyShip(kind)
{
    position.x = firstPos.x;
    position.z = firstPos.z;
    direction = VNorm(VSub(setDestinationPos, VGet(position.x, setDestinationPos.y, position.z)));
}