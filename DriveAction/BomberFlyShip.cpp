#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"
#include "ReusableTimer.h"
//����
float BomberFlyShip::speed = 14.0f;
/// <summary>
/// ���e���󂩂痎�Ƃ����
/// </summary>
/// <param name="setFirstPos"></param>
/// <param name="setDestinationPos"></param>
/// <param name="initParam"></param>
BomberFlyShip::BomberFlyShip(VECTOR setFirstPos,VECTOR setDestinationPos, FlyShipInit::InitFlyShipParamator initParam)
    :FlyShip(ObjectInit::bomberShip)
{   
    setFirstPos.y = position.y;
    setDestinationPos.y = position.y;
    position = setFirstPos;
    direction = VNorm(VSub(setDestinationPos, position));
    direction.y = 0;
    bombFallTimer = new ReusableTimer(initParam.setCoolTime);
    aliveTimer = new Timer(initParam.setAliveTime);
    speed = initParam.moveSpeed;

    SoundPlayer::LoadSound(bomberShipFlight);
    SoundPlayer::Play3DSE(bomberShipFlight);

    velocity = VScale(direction, speed);
}
/// <summary>
/// ���e�𗎂Ƃ��Ȃ���i��
/// </summary>
void BomberFlyShip::Update()
{
    //�x���V�e�B�𔽉f
    ReflectsVelocity();
    //�N�[���^�C�����I�������
    if (bombFallTimer->IsOverLimitTime())
    {
        //���e�𓊉�
        DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::bomber,sub);
        bombFallTimer->Reuse();
    }
    //�������Ԃ��߂����玀�S
    if (aliveTimer->IsOverLimitTime())
    {
        objState = dead;
    }
    
    //���ł��鉹�̈ʒu���X�V
    SoundPlayer::SetPosition3DSound(position, bomberShipFlight);
}
