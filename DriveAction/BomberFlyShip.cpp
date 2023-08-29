#include <iostream>
#include <memory>
#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "AssetManager.h"
#include "ReusableTimer.h"
/// <summary>
/// 爆弾を空から落とすやつ
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
/// 爆弾を落としながら進む
/// </summary>
void BomberFlyShip::Update()
{
    //クールタイムが終わったら
    if (bombFallTimer->IsOverLimitTime())
    {
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(DamageObjectGenerator::bomber, std::make_unique<ObjectObserver>(this));
        bombFallTimer->Reuse();
    }
}
