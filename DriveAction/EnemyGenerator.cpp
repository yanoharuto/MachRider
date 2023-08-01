#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "SawController.h"
#include "BomberFlyShipController.h"
#include "ActorController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "ActorControllerManager.h"

EnemyGenerator::EnemyGenerator(ActorControllerManager* controllerManager)
{
    editDataVec = FirstPositionGetter::GetInitData(Object::damageObject);
    enemyMap[saw] = new SawController();
    controllerManager->AddActorController(enemyMap[saw]);
    enemyMap[circleLaserShip] = new CircleFlyShipController();
    controllerManager->AddActorController(enemyMap[circleLaserShip]);
    enemyMap[bomberShip] = new BomberFlyShipController();
    controllerManager->AddActorController(enemyMap[bomberShip]);
    enemyMap[upDownLaserShip] = new UpDownFlyShipController();
    controllerManager->AddActorController(enemyMap[upDownLaserShip]);
    enemyMap[bomberShip] = new BomberFlyShipController();
    controllerManager->AddActorController(enemyMap[bomberShip]);
    enemyMap[moveSaw] = new MoveSawController();
    controllerManager->AddActorController(enemyMap[moveSaw]);
}
void EnemyGenerator::GenerateEnemys(int collectNum)
{
    for (auto mapItr = enemyMap.begin(); mapItr != enemyMap.end(); mapItr++)
    {
        (*mapItr).second->AddObject(GetNowEnemyEditData((*mapItr).first,collectNum));
    }
}
std::vector<EditArrangementData> EnemyGenerator::GetNowEnemyEditData(InitObjKind kind, int collectNum)
{
    std::vector<EditArrangementData> editData;
    for (int i = 0; i < editDataVec.size(); i++)
    {
        ObjectInit::InitObjKind dataKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
        if (editDataVec[i].missionNum == collectNum && kind == dataKind)
        {
            editData.push_back(editDataVec[i]);
        }
    }
    return editData;
}