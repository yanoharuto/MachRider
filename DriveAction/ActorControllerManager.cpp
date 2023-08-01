#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "EnemyGenerator.h"
//actor�Ǘ��N���X�̃��X�g
std::list<ActorController*> ActorControllerManager::actorControllerList;
/// <summary>
/// actor�̓����𐧌䂵�Ă��镨��S�����˂ē�����
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
    enemyGenerator = new EnemyGenerator(this);
    damageObjGenerator = new DamageObjectGenerator(this);
    enemyGenerator->GenerateEnemys(0);
}

ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorControllerList.clear();
}
/// <summary>
/// �X�V
/// </summary>
void ActorControllerManager::Update()
{
    //�G��������
    GenerateEnemyProcess();
    //�X�V����
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Update();
    }
}
/// <summary>
/// �Q�[���J�n�O�X�V
/// </summary>
void ActorControllerManager::GameReserve()
{
    //�G��������
    GenerateEnemyProcess();
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->GameReserve();
    }
}
/// <summary>
/// �e�A�N�^�[�̕`��
/// </summary>
void ActorControllerManager::Draw()const
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}
/// <summary>
/// actor�Ǘ��N���X��ǉ�
/// </summary>
/// <param name="actorController"></param>
void ActorControllerManager::AddActorController(ActorController* actorController)
{
    if (actorController != nullptr)
    {
        actorControllerList.push_back(actorController);
    }
}

/// <summary>
///�@�G��������
/// </summary>
void ActorControllerManager::GenerateEnemyProcess()
{
    int nowGetCollectNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    if (nowGetCollectNum != collectNum)
    {
        collectNum = nowGetCollectNum;
        enemyGenerator->GenerateEnemys(collectNum);
    }
}
