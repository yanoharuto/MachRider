#include "UpDownLaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include <math.h>
//totalMoveValueの増加量
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
//上下に動く速度
const float UpDownLaserFlyShip::updownSpeed = 6.0f;
/// <summary>
/// 上下に動きながらレーザーを出すやつ
/// </summary>
UpDownLaserFlyShip::UpDownLaserFlyShip(EditArrangementData editData)
    :LaserFlyShip(ObjectInit::upDownLaserShip)
{
    GenerateLaser(DamageObjectGenerator::bigRadLaser);
    position.x = editData.posX;
    position.z = editData.posZ;
    direction = VGet(editData.dirX, 0, editData.dirZ);
}
/// <summary>
/// 上下に動くよ
/// </summary>
void UpDownLaserFlyShip::Update()
{
    //上下に移動
    objState = active;
    totalMoveValue += addMoveValue;
    position.y = cosf(totalMoveValue) * updownSpeed + firstPosY;
}
