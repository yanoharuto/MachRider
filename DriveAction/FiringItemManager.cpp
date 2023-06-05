#include "FiringItemManager.h"
#include "Rocket.h"
#include "Utility.h"
#include "ListUtility.h"
#include "DamageObject.h"
#include "DamageObjectGenerator.h"
//�I�u�W�F�N�g�^�O��DamageObject�ɂȂ��Ă�I�u�W�F�N�g�̃��X�g
std::list<DamageObject*> FiringItemManager::damageObjList;

FiringItemManager::FiringItemManager()
{
    damageObjGenerator = new DamageObjectGenerator();
}

FiringItemManager::~FiringItemManager()
{
    for (auto ite = damageObjList.begin(); ite != damageObjList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
    damageObjList.clear();
}

void FiringItemManager::AddFiringObject(DamageObject* damageObj)
{
    if (damageObj != nullptr)
    {
        damageObjList.push_back(damageObj);
    }
}

void FiringItemManager::Update()
{
    //�C�e���[�^�[
    auto objIte = damageObjList.begin();
    //�������Ă�������X�g
    std::list<Actor*> brokenList;
    //�X�V����K�v�������Ȃ��������
    while (objIte != damageObjList.end())
    {
        (*objIte)->Update();
        if (!(*objIte)->GetAliveFlag()) //�������݂��Ă��Ȃ�������X�V�I��
        {
            brokenList.push_back((*objIte));

            objIte = damageObjList.erase(objIte);//erase�͏������C�e���[�^�[�̎��̓z��Ԃ�
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
}

void FiringItemManager::Draw()
{
    for (auto objIte = damageObjList.begin(); objIte != damageObjList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}