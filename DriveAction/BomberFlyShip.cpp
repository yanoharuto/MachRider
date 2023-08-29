#include <iostream>
#include <memory>
#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "AssetManager.h"
#include "ReusableTimer.h"
/// <summary>
/// ���e���󂩂痎�Ƃ����
/// </summary>
/// <param name="setFirstPos"></param>
/// <param name="setDestinationPos"></param>
/// <param name="initParam"></param>
BomberFlyShip::BomberFlyShip(PlacementData data, FlyShipInit::InitFlyShipParamator initParam)
    :FlyShip(bomberShip)
{
    position.x = data.posX;
    position.z = data.posZ;
    direction.x=data.dirX;
    direction.z=data.dirZ;
    direction.y = 0;
    bombFallTimer = new ReusableTimer(initParam.setCoolTime);

    velocity = direction;
}
/// <summary>
/// ���e�𗎂Ƃ��Ȃ���i��
/// </summary>
void BomberFlyShip::Update()
{
    //�N�[���^�C�����I�������
    if (bombFallTimer->IsOverLimitTime())
    {
        //���e�𓊉�
        DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::bomber, std::make_unique<ObjectObserver>(this));
        bombFallTimer->Reuse();
    }
}
