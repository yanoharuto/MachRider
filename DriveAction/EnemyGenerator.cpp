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
/// �����̃}�l�[�W���[�ɓZ�߂ē��������n���Ă���
/// </summary>
/// <param name="controllerManager"></param>
void EnemyGenerator::CreateEnemy(ActorControllerManager* controllerManager)
{
    
    int collectGetNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    //�O��G���o�����Ƃ��Ǝ��W�A�C�e���̐����������ǉ�
    if (collectNum != collectGetNum && totalCollectNum > collectGetNum)
    {
        collectNum = collectGetNum;
        //���ꂽ���W�A�C�e���̐��ŏo���G�l�~�[��ύX
        CreateActorController(circleLaserShip, challengeDataVec[collectNum].enemyPos,controllerManager);
        
        CreateActorController(upDownLaserShip, challengeDataVec[collectNum].enemyPos, controllerManager);
        
        CreateActorController(saw, challengeDataVec[collectNum].enemyPos, controllerManager);
    }
    
}
/// <summary>
/// �G�@��Z�߂ē������z���쐬
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