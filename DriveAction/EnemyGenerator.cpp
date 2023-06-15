#include "EnemyGenerator.h"
#include "CircleFlyshipCommander.h"
#include "UpDownFlyShipCommander.h"
#include "Utility.h"
#include "InitActor.h"
#include "InitObjKind.h"
#include "Saw.h"
std::vector<ActorController*> EnemyGenerator::CreateActorController(InitObjKind kind, std::unordered_map<int,std::vector<VECTOR>> generatePosMap)
{
    auto firstPosVec = generatePosMap[InitActor::GetActorTileNum(kind)];
    std::vector<ActorController*> commander;
    for (auto ite = firstPosVec.begin(); ite != firstPosVec.end(); ite++)
    {
        switch (kind)
        {
        case upDownLaserShip:
            commander.push_back(new UpDownFlyShipCommander(*ite));
            break;
        case circleLaserShip:
            commander.push_back(new CircleFlyshipCommander(*ite));
            break;
        case saw:
            commander.push_back(new ActorController(new Saw((*ite))));
        default:
            break;
        }
    }
    return commander;
}
