#include "DamageObjectGenerator.h"
#include "Rocket.h"
#include "LittleRadiusLaser.h"
#include "BigRadiusLaser.h"
#include "FiringItemManager.h"
#include "DamageObject.h"
#include "ObjectObserver.h"

DamageObjectGenerator::DamageObjectGenerator()
{    

}
DamageObjectGenerator::~DamageObjectGenerator()
{
}
/// <summary>
/// アイテムの種類によって生成するアイテムを変更する
/// </summary>
/// <param name="itemTag"></param>
/// <param name="carInfo"></param>
DamageObject* DamageObjectGenerator::GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub)
{
    DamageObject* obj = nullptr;
    ObjectObserver* observer = new ObjectObserver(sub);
    switch (itemTag)
    {
    case Item:: bomber:
        obj = new Rocket(observer);
        break;
    case Item::littleRadLaser:
        obj = new LittleRadiusLaser(observer);
        break;
    case Item::bigRadLaser:
        obj = new BigRadiusLaser(observer);
        break;
    default:
        break;
    }
    
    FiringItemManager::AddFiringObject(obj);
    return obj;
}