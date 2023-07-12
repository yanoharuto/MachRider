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
/// <summary>
/// 引数のマネージャーに纏めて動かすやつを渡していく
/// </summary>
/// <param name="controllerManager"></param>
void EnemyGenerator::CreateEnemy(ActorControllerManager* controllerManager)
{
    
    int collectGetNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    //前回敵を出したときと収集アイテムの数が違ったら追加
    if (collectNum != collectGetNum && totalCollectNum > collectGetNum)
    {
        collectNum = collectGetNum;
        //取られた収集アイテムの数で出すエネミーを変更
        CreateActorController(circleLaserShip, challengeDataVec[collectNum].enemyPos,controllerManager);
        
        CreateActorController(upDownLaserShip, challengeDataVec[collectNum].enemyPos, controllerManager);
        
        CreateActorController(saw, challengeDataVec[collectNum].enemyPos, controllerManager);
    }
    
}
/// <summary>
/// 敵機を纏めて動かす奴を作成
/// </summary>
/// <param name="kind"></param>
/// <param name="generatePosMap"></param>
/// <param name="controllerManager"></param>
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