#include <iostream>
#include <memory>
#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "AssetManager.h"
#include "ReusableTimer.h"
/// <summary>
/// 引数の位置に生成　
/// </summary>
/// <param name="data">生成位置と向きが入った構造体</param>
/// <param name="initParam">爆弾発射クールタイムを所得</param>
/// <param name="damageObjGenerator">爆弾発射に必要なクラス</param>
BomberFlyShip::BomberFlyShip(PlacementData data, FlyShipInit::InitFlyShipParamator initParam, std::shared_ptr<DamageObjectGenerator> damageObjGenerator)
    :Actor(InitObjKind::bomberShip)
{
    position.x = data.posX;
    position.z = data.posZ;
    direction.x = data.dirX;
    direction.z = data.dirZ;
    direction.y = 0;
    bombFallTimer = new ReusableTimer(initParam.setCoolTime);

    damageObjectGenerator = damageObjGenerator;
    velocity = direction;
}
/// <summary>
/// damageObjectGeneratorの開放
/// </summary>
BomberFlyShip::~BomberFlyShip()
{
    damageObjectGenerator.reset();
}
/// <summary>
/// 爆弾を落としながら進む
/// </summary>
void BomberFlyShip::Update()
{
    //クールタイムが終わったら
    if (bombFallTimer->IsOverLimitTime())
    {
        //クールタイム再セット
        bombFallTimer->Reuse();
        //爆弾を投下
        damageObjectGenerator->GenerateDamageObject(DamageObjectGenerator::bomber, std::make_unique<ObjectObserver>(this));
    }
}
