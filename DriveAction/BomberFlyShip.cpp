#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"

//速さ
float BomberFlyShip::speed = 14.0f;

BomberFlyShip::BomberFlyShip(VECTOR setFirstPos,VECTOR setDestinationPos, FlyShipInit::InitFlyShipParamator initParam)
    :FlyShip(ObjectInit::bomberShip)
{   
    setFirstPos.y = position.y;
    setDestinationPos.y = position.y;
    position = setFirstPos;
    direction = VNorm(VSub(setDestinationPos, position));
    direction.y = 0;
    bombFallTimer = new Timer(initParam.setCoolTime);
    aliveTimer = new Timer(initParam.setAliveTime);
    speed = initParam.moveSpeed;

    SoundPlayer::LoadSound(bomberShipFlight);
    SoundPlayer::Play3DSE(bomberShipFlight);
}

void BomberFlyShip::Update()
{
    velocity = VScale(direction, speed);

    //クールタイムが終わったら
    if (bombFallTimer->IsOverLimitTime())
    {
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(Item::bomber,sub);
        bombFallTimer->Init();
    }
    if (aliveTimer->IsOverLimitTime())
    {
        objState = dead;
    }
    SoundPlayer::SetPosition3DSound(position, bomberShipFlight);
    UpdatePosition();
}
