#include "ActorControllerManager.h"
#include "AddableObjectController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "EnemyGenerator.h"
#include "CircleFlyShipController.h"
#include "UpDownFlyShipController.h"
#include "MoveSawController.h"
#include "BomberFlyShipController.h"
#include "SawController.h"
#include "RotatingLaserController.h"
#include "BomberController.h"
#include "StageObjectController.h"
/// <summary>
/// �Q�[�����Ɏg���I�u�W�F�N�g�̊Ǘ��N���X�̊m��
/// </summary>
/// <param name="collectItemObserver">���W�A�C�e�������ꂽ�肵���狳���Ă��炤</param>
ActorControllerManager::ActorControllerManager(std::shared_ptr<CollectItemObserver> collectItemObserver)
{
    collectObserver = collectItemObserver;
    //�X�e�[�W�̐���
    actorControllerList.push_back(std::make_shared<StageObjectController>());
    //���[�U�[�Ǘ��N���X
    std::shared_ptr<RotatingLaserController> laserController = std::make_shared<RotatingLaserController>();
    //���e�Ǘ��N���X
    std::shared_ptr<BomberController> bombController = std::make_shared<BomberController>();
    //�_���[�W���肠��I�u�W�F�N�g�����N���X
    damageObjGenerator = std::make_shared<DamageObjectGenerator>(laserController, bombController);
    actorControllerList.push_back(laserController);
    actorControllerList.push_back(bombController);
    //�e�G�Ǘ��N���X
    addableActorControllerList.push_back(std::make_shared<SawController>());
    addableActorControllerList.push_back(std::make_shared<MoveSawController>());
    addableActorControllerList.push_back(std::make_shared<CircleFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<BomberFlyShipController>(damageObjGenerator));
    addableActorControllerList.push_back(std::make_shared<UpDownFlyShipController>(damageObjGenerator));
    //�G�����N���X
    enemyGenerator = new EnemyGenerator();
    //�I�u�W�F�N�g�𐶐�
    for (auto ctrItr = addableActorControllerList.begin(); ctrItr != addableActorControllerList.end(); ctrItr++)
    {
        enemyGenerator->GenerateEnemys(0, *ctrItr);
    }
}
/// <summary>
/// �Ǘ��N���X��X�e�[�W�̃I�u�W�F�N�g�Ȃǂ����ׂĉ��
/// </summary>
ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    for (auto ite = addableActorControllerList.begin(); ite != addableActorControllerList.end(); ite++)
    {
        (*ite).reset();
    }
    damageObjGenerator.reset();
    SAFE_DELETE(enemyGenerator);
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
void ActorControllerManager::AddActorController(std::shared_ptr<ActorController> actorController)
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
void ActorControllerManager::PrepareGame(std::list<std::shared_ptr<controllerClass>> controllerList)
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
void ActorControllerManager::Update(std::list<std::shared_ptr<controllerClass>> controllerList)
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
void ActorControllerManager::Draw(std::list<std::shared_ptr<controllerClass>> controllerList)const
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
    int nowGetCollectNum = collectObserver->GetCollectCount();
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