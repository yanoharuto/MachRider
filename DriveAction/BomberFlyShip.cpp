#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"
#include "ReusableTimer.h"
//速さ
float BomberFlyShip::speed = 14.0f;
/// <summary>
/// 爆弾を空から落とすやつ
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
/// 爆弾を落としながら進む
/// </summary>
void BomberFlyShip::Update()
{
    //ベロシティを反映
    ReflectsVelocity();
    //クールタイムが終わったら
    if (bombFallTimer->IsOverLimitTime())
    {
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::bomber,sub);
        bombFallTimer->Reuse();
    }
    //生存時間を過ぎたら死亡
    if (aliveTimer->IsOverLimitTime())
    {
        objState = dead;
    }
    
    //飛んでいる音の位置を更新
    SoundPlayer::SetPosition3DSound(position, bomberShipFlight);
}
