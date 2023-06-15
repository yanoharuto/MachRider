#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "LittleRadiusLaserController.h"
#include "BigRadiusLaserController.h"
#include "ObjectObserver.h"
#include "ActorController.h"
#include "ActorControllerManager.h"

std::list<ActorController*> DamageObjectGenerator::createDamageObject;
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
void DamageObjectGenerator::GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub)
{
    ActorController* obj = nullptr;
    
    switch (itemTag)
    {
    case Item:: bomber:
        obj = new BomberController(sub);
        break;
    case Item::littleRadLaser:
        obj = new LittleRadiusLaserController(sub);
        break;
    case Item::bigRadLaser:
        obj = new BigRadiusLaserController(sub);
        break;
    default:
        break;
    }
    createDamageObject.push_back(obj);
}

void DamageObjectGenerator::GetObjectList(ActorControllerManager* controllerManager)
{
    for (auto ite = createDamageObject.begin(); ite != createDamageObject.end(); ite++)
    {
        controllerManager->AddActorController(std::move(*ite));
    }
    createDamageObject.clear();
}
