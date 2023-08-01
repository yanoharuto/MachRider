#include "DamageObjectGenerator.h"
#include "BomberController.h"
#include "LittleRadiusLaserController.h"
#include "BigRadiusLaserController.h"
#include "ObjectObserver.h"
#include "DamageObjectController.h"
#include "ActorControllerManager.h"
//�쐬�����R���g���[���[�N���X�BGetControllerList���Ă΂��Ə����������
std::unordered_map<DamageObjectGenerator::DamageObjectKind, DamageObjectController*> DamageObjectGenerator::controllerVec;
/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
DamageObjectGenerator::DamageObjectGenerator(ActorControllerManager* const controllerManager)
{
    controllerVec.clear();
    controllerVec.insert(std::make_pair(bomber, new BomberController()));
    controllerVec.insert(std::make_pair(littleRadLaser, new BigRadiusLaserController()));
    controllerVec.insert(std::make_pair(bigRadLaser, new LittleRadiusLaserController()));
    
    controllerManager->AddActorController(controllerVec[bomber]);
    controllerManager->AddActorController(controllerVec[bigRadLaser]);
    controllerManager->AddActorController(controllerVec[littleRadLaser]);
}
DamageObjectGenerator::~DamageObjectGenerator()
{
    controllerVec.clear();
}
/// <summary>
/// �_���[�W��^����I�u�W�F�N�g�𐶐�
/// </summary>
/// <param name="itemTag"></param>
/// <param name="sub">���˂����l�̏���n��</param>
/// <returns></returns>
void DamageObjectGenerator::GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub)
{
    controllerVec[itemTag]->AddObject(std::move(sub));
}