#include "ActorControllerManager.h"
#include "ActorController.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "DxLib.h"
std::list<ActorController*> ActorControllerManager::actorControllerList;
ActorControllerManager::ActorControllerManager()
{
    actorControllerList.clear();
}

ActorControllerManager::~ActorControllerManager()
{
    for (auto ite = actorControllerList.begin(); ite != actorControllerList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    actorControllerList.clear();
}

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
    damageObjGenerator->GetObjectList(this);
}

void ActorControllerManager::GameReserve()
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->GameReserve();
    }
}

void ActorControllerManager::Draw()const
{
    for (auto objIte = actorControllerList.begin(); objIte != actorControllerList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}

void ActorControllerManager::AddActorController(ActorController* actorController)
{
    if (actorController != nullptr)
    {
        actorControllerList.push_back(actorController);
    }
}
