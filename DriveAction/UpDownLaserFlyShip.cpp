#include "UpDownLaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include <math.h>
//totalMoveValue�̑�����
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
//�㉺�ɓ������x
const float UpDownLaserFlyShip::updownSpeed = 6.0f;
/// <summary>
/// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
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
/// �㉺�ɓ�����
/// </summary>
void UpDownLaserFlyShip::Update()
{
    //�㉺�Ɉړ�
    objState = active;
    totalMoveValue += addMoveValue;
    position.y = cosf(totalMoveValue) * updownSpeed + firstPosY;
}
