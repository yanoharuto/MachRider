#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
#include "EnemyGenerator.h"
//actor�Ǘ��N���X�̃��X�g
std::list<ActorController*> ActorControllerManager::actorControllerList;
/// <summary>
/// actor�̓����𐧌䂵�Ă��镨��S�����˂ē�����
/// </summary>
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
    enemyGenerator = new EnemyGenerator();
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
    //�C�e���[�^�[
    auto objIte = actorControllerList.begin();
    //�������Ă�������X�g
    std::list<ActorController*> brokenList;
    //�X�V����K�v�������Ȃ��������
    while (objIte != actorControllerList.end())
    {
        (*objIte)->Update();
        //�������݂��Ă��Ȃ�������X�V�I��
        if (!(*objIte)->IsAlive()) 
        {
            brokenList.push_back((*objIte));

            objIte = actorControllerList.erase(objIte);//erase�͏������C�e���[�^�[�̎��̓z��Ԃ�
        }
        else
        {
            ++objIte;//���������ɍ���Ȃ������玟��
        }
    }
    //�����Ă��������
    for (auto ite = brokenList.begin(); ite != brokenList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    //�������̏����ŃI�u�W�F�N�g�����₵���A�C�e��������Ă���
    damageObjGenerator->MoveControllerList(this);
    enemyGenerator->GetActorControllerVector(this);
}
/// <summary>
/// �Q�[���J�n�O�X�V
/// </summary>
void ActorControllerManager::GameReserve()
{
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
