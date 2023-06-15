#include "ChallengeFlow.h"
#include "Utility.h"
#include "ObjectObserver.h"
#include "InitActor.h"
#include "ActorControllerManager.h"
#include "EnemyGenerator.h"
#include "CollectController.h"
ChallengeFlow::ChallengeFlow(std::weak_ptr<ObjectObserver> player)
{
    auto getter = new FirstPositionGetter();
    challengeDataVec = getter->GetChallengeData();
    totalCollectNum = challengeDataVec.size();
    playerObserver = player;
    enemyCreator = new EnemyGenerator();
}

ChallengeFlow::~ChallengeFlow()
{
}

/// <summary>
/// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̐�
/// </summary>
/// <returns></returns>
int ChallengeFlow::GetTotalCollectNum()
{
    return totalCollectNum;
}

/// <summary>
/// �v���C���[���A�C�e����S����������Ȃ�
/// </summary>
/// <returns></returns>
bool ChallengeFlow::IsEndingChallenge()
{
    return totalCollectNum == playerObserver.lock()->GetSubjectHitCount(Object::collect);
}

/// <summary>
/// �v���C���[���A�C�e�������������controllerManager���X�V
/// </summary>
/// <param name="controllerManager"></param>
void ChallengeFlow::Update(ActorControllerManager* controllerManager)
{
    int collectGetNum = playerObserver.lock()->GetSubjectHitCount(Object::collect);
    if (collectNum != collectGetNum && totalCollectNum > collectGetNum)
    {
        collectNum = collectGetNum ;
        AddEnemyController(circleLaserShip, controllerManager);
        AddEnemyController(upDownLaserShip, controllerManager);
        AddEnemyController(saw, controllerManager);
        controllerManager->AddActorController(new CollectController(challengeDataVec[collectNum].collectPos[0][0]));
    }   
}
/// <summary>
/// �v���C���[���A�C�e�������������G�l�~�[�ǉ�
/// </summary>
/// <param name="objTag"></param>
/// <param name="controllerManager"></param>
void ChallengeFlow::AddEnemyController(ObjectInit::InitObjKind objTag, ActorControllerManager* controllerManager)
{
    auto enemyVec = enemyCreator->CreateActorController(objTag,challengeDataVec[collectNum].enemyPos);
    for (auto ite = enemyVec.begin(); ite != enemyVec.end(); ite++)
    {
        controllerManager->AddActorController((*ite));
    }
}