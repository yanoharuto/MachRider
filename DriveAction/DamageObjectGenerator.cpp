#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "LittleRadiusLaserController.h"
#include "BigRadiusLaserController.h"
#include "ObjectObserver.h"
#include "ActorController.h"
#include "ActorControllerManager.h"
//�쐬�����R���g���[���[�N���X�BGetControllerList���Ă΂��Ə����������
std::list<ActorController*> DamageObjectGenerator::createDamageObject;
/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
DamageObjectGenerator::DamageObjectGenerator()
{    

}
DamageObjectGenerator::~DamageObjectGenerator()
{
}
/// <summary>
/// �_���[�W��^����I�u�W�F�N�g�𐶐�
/// </summary>
/// <param name="itemTag"></param>
/// <param name="sub">���˂����l�̏���n��</param>
/// <returns></returns>
void DamageObjectGenerator::GenerateDamageObject(DamageObjectKind itemTag,ObjectSubject* sub)
{
    ActorController* obj = nullptr;
    
    switch (itemTag)
    {
    case  bomber:
        obj = new BomberController(sub);
        break;
    case littleRadLaser:
        obj = new LittleRadiusLaserController(sub);
        break;
    case bigRadLaser:
        obj = new BigRadiusLaserController(sub);
        break;
    default:
        break;
    }
    createDamageObject.push_back(obj);
}
/// <summary>
/// �������ꂽ�I�u�W�F�N�g��controllerManager�ɒǉ�
/// </summary>
/// <param name="controllerManager"></param>
void DamageObjectGenerator::MoveControllerList(ActorControllerManager* controllerManager)
{
    for (auto ite = createDamageObject.begin(); ite != createDamageObject.end(); ite++)
    {
        controllerManager->AddActorController(std::move(*ite));
    }
    createDamageObject.clear();
}
