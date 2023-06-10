#include "EnemyManager.h"
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
EnemyManager::EnemyManager(RacerManager* racerManager)
{
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
    auto challengeVec = FirstPositionGetter::GetChallengeData();

    for (int i = 0; i < challengeVec.size(); i++)
    {
        for (int j = 0; j < challengeVec[i].enemyPos.size(); j++)
        {
            for (int n = 0; n < challengeVec[i].enemyPos[j].size(); n++)
            {
                VECTOR firstPos = challengeVec[i].enemyPos[j][n];
                FlyShipCommander* commander;
                switch (j)
                {
                case 0:
                    commander = new UpDownFlyShipCommander(firstPos);
                    break;
                case1:
                default:
                    commander = new CircleFlyshipCommander(firstPos);
                    break;
                }
                commanderMap[i].push_back(commander);
            }
        }
    }
}

EnemyManager::~EnemyManager()
{
    int key = commanderMap.size();
    for (int i = 0; i < key; i++)
    {
        for (auto ite = commanderMap[i].begin(); ite != commanderMap[i].end(); ite++)
        {
            SAFE_DELETE(*(ite));
        }
    }
}

void EnemyManager::Update()
{
    int key = playerObserver->GetSubjectHitCount(Object::coin) + 1;
    for (int i = 0; i < key; i++)
    {
        for (auto ite = commanderMap[i].begin(); ite != commanderMap[i].end(); ite++)
        {
            (*ite)->Update();
        }
    }
}

void EnemyManager::Draw()
{
    int key = playerObserver->GetSubjectHitCount(Object::coin) + 1;
    for (int i = 0; i < key; i++)
    {
        for (auto ite = commanderMap[i].begin(); ite != commanderMap[i].end(); ite++)
        {
            (*ite)->Draw();
        }
    }
}