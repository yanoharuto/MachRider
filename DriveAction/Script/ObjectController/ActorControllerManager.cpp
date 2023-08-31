#include "ActorControllerManager.h"
#include "AddableObjectController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "SawController.h"
/// <summary>
/// �G�Ȃǂ�New���Ĕz�u����
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    //�G�����N���X
    enemyGenerator = new EnemyGenerator();
    //�_���[�W���肠��I�u�W�F�N�g�����N���X
    damageObjGenerator = new DamageObjectGenerator(this);
    //�e�G�Ǘ��N���X
    addableActorControllerList.push_back(new SawController());
    addableActorControllerList.push_back(new MoveSawController());
    addableActorControllerList.push_back(new CircleFlyShipController());
    addableActorControllerList.push_back(new BomberFlyShipController());
    addableActorControllerList.push_back(new UpDownFlyShipController());
    //�I�u�W�F�N�g�𐶐�
    for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
    {
        enemyGenerator->GenerateEnemys(0,*ctrItr);
    }
}
/// <summary>
/// �G�̊Ǘ��N���X��X�e�[�W�̃I�u�W�F�N�g�Ȃǂ����ׂĉ��
/// </summary>
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
    Update(actorControllerList);
    Update(addableActorControllerList);
}
/// <summary>
/// �Q�[���J�n�O�X�V
/// </summary>
void ActorControllerManager::PrepareGame()
{
    //�G��������
    GenerateEnemyProcess();
    PrepareGame(actorControllerList);
    PrepareGame(addableActorControllerList);
}
/// <summary>
/// �e�A�N�^�[�̕`��
/// </summary>
void ActorControllerManager::Draw()const
{
    Draw(actorControllerList);
    Draw(addableActorControllerList);
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
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����Q�[���J�n�O�X�V
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::PrepareGame(std::list<controllerClass*> controllerList)
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->PrepareGame();
    }
}
/// <summary>
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����X�V
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::Update(std::list<controllerClass*> controllerList)
{
    //�X�V����
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Update();
    }
}
/// <summary>
/// 2��Actor�Ǘ��N���X�ǂ���ł��g����`��
/// </summary>
/// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
/// <param name="controllerList">controllerClass��Z�߂����X�g</param>
template<typename controllerClass>
void ActorControllerManager::Draw(std::list<controllerClass*> controllerList)const
{
    for (auto objIte = controllerList.begin(); objIte != controllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}
/// <summary>
///�@�G��������
/// </summary>
void ActorControllerManager::GenerateEnemyProcess()
{
    //���W�A�C�e�������ꂽ��
    int nowGetCollectNum = CollectController::GetTotalCollectNum() - CollectController::GetRemainingCollectNum();
    //���ꂽ�����X�V���ꂽ��
    if (nowGetCollectNum != collectNum)
    {
        //�G�����N���X�ɒǉ�����K�v�����鎖��������
        for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
        {
            collectNum = nowGetCollectNum;
            enemyGenerator->GenerateEnemys(collectNum,*ctrItr);
        }
    }
}