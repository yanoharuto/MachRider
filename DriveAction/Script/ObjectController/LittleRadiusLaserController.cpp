#include "LittleRadiusLaserController.h"
#include "LittleRadiusLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// ������y����]���郌�[�U�[�̍X�V��
/// </summary>
LittleRadiusLaserController::LittleRadiusLaserController()
    :DamageObjectController(ObjectInit::littleRadiusLaser)
{

};
/// <summary>
/// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
/// </summary>
/// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
void LittleRadiusLaserController::OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new LittleRadiusLaser(std::move(sub)));
}
