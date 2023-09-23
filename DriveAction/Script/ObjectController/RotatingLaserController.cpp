#include "RotatingLaserController.h"
#include "RotatingLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// �ǉ��ƕ`��̏���
/// </summary>
/// <param name="generator">���[�U�[������</param>
RotatingLaserController::RotatingLaserController()
    :DamageObjectController(ObjectInit::InitObjKind::laser)
{
};
/// <summary>
/// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
/// </summary>
/// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
void RotatingLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new RotatingLaser(std::move(sub)));
}