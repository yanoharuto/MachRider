#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
#include "ObjectObserver.h"
/// <summary>
/// 位置と向きを初期化してレーザーを発射
/// </summary>
/// <param name="setPos">位置</param>
/// <param name="setDestinationPos">向くべき方向の位置</param>
/// <param name="damageObjectGenerator">レーザーを発射することを伝えるクラス</param>
CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos, std::weak_ptr<DamageObjectGenerator> damageObjectGenerator)
    :Actor(ObjectInit::InitObjKind::circleLaserShip)
{
    position.x = firstPos.x;
    position.z = firstPos.z;
    setDestinationPos.y = position.y;
    direction = VNorm(VSub(setDestinationPos, position));
    //レーザーを発射
    damageObjectGenerator.lock()->GenerateDamageObject(DamageObjectGenerator::laser, std::make_unique<ObjectObserver>(this));   
}