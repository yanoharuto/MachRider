#include "FlyShipManager.h"
#include "CircleFlyshipCommander.h"
#include "UpDownFlyShipCommander.h"
#include "Utility.h"
#include "FlyShipCommander.h"
#include "RacerManager.h"
#include "FirstPositionGetter.h"
#include "Object.h"
/// <summary>
/// 空を飛ぶ船のマネージャー
/// </summary>
/// <param name="racerManager"></param>
FlyShipManager::FlyShipManager(RacerManager* racerManager)
{
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
    auto challengeVec = FirstPositionGetter::GetChallengeData();

    for (int i = 0; i < challengeVec.size(); i++)
    {
        int n = 0;
        
        for (int j = 0; j < challengeVec[i].enemyPos.size(); j++)
        {
            VECTOR firstPos = challengeVec[i].enemyPos[j][n];
            FlyShipCommander* commander;
            switch (i)
            {
            case 0:
                commander = new UpDownFlyShipCommander(firstPos);
                break;
            case1:
                commander = new CircleFlyshipCommander(firstPos);
                break;
            default:
                break;
            }
            n++;
            commanderMap[i].push_back(commander);
        }
    }
}

FlyShipManager::~FlyShipManager()
{
    int key = commanderMap.size();
    for (auto ite = commanderMap[0].begin(); ite != commanderMap[key].end(); ite++)
    {
        SAFE_DELETE(*(ite));
    }
}

void FlyShipManager::Update()
{
    
    int key = playerObserver->GetObjHitCount(Object::coin);
    for (auto ite = commanderMap[0].begin(); ite != commanderMap[key].end(); ite++)
    {
        (*ite)->Update();
    }
}

void FlyShipManager::Draw()
{
    int key = playerObserver->GetObjHitCount(Object::coin);
    for (auto ite = commanderMap[0].begin(); ite != commanderMap[key].end(); ite++)
    {
        (*ite)->Draw();
    }
}