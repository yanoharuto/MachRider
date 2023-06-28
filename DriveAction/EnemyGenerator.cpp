#include "EnemyGenerator.h"
#include "CircleFlyshipCommander.h"
#include "UpDownFlyShipCommander.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Saw.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "InitActor.h"
#include "ActorControllerManager.h"
#include "CollectController.h"

EnemyGenerator::EnemyGenerator()
{
    auto getter = new FirstPositionGetter();
    challengeDataVec = getter->GetChallengeData();
    totalCollectNum = challengeDataVec.size();
}
void EnemyGenerator::GetActorControllerVector(ActorControllerManager* controllerManager)
{
    int collectGetNum = CollectController::TotalCollectNum() - CollectController::GetRemainingCollectNum();
    
    if (collectNum != collectGetNum && totalCollectNum > collectGetNum)
    {
        collectNum = collectGetNum;
        CreateActorController(circleLaserShip, challengeDataVec[collectNum].enemyPos,controllerManager);
        
        CreateActorController(upDownLaserShip, challengeDataVec[collectNum].enemyPos, controllerManager);
        
        CreateActorController(saw, challengeDataVec[collectNum].enemyPos, controllerManager);
    }
    
}
void EnemyGenerator::CreateActorController(InitObjKind kind, std::unordered_map<int,std::vector<VECTOR>> generatePosMap, ActorControllerManager* controllerManager)
{
    auto firstPosVec = generatePosMap[InitActor::GetActorTileNum(kind)];
    for (auto ite = firstPosVec.begin(); ite != firstPosVec.end(); ite++)
    {
        switch (kind)
        {
        case upDownLaserShip:
            controllerManager->AddActorController(new UpDownFlyShipCommander(*ite));
            break;
        case circleLaserShip:
            controllerManager->AddActorController(new CircleFlyshipCommander(*ite));
            break;
        case saw:
            controllerManager->AddActorController(new ActorController(new Saw((*ite))));
        default:
            break;
        }
    }
 
}