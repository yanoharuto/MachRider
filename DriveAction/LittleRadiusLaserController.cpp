#include "LittleRadiusLaserController.h"
#include "LittleRadiusLaser.h"
#include "ObjectObserver.h"
/// <summary>
/// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
/// </summary>
/// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
void LittleRadiusLaserController::AddObject(std::unique_ptr<ObjectObserver> sub)
{
    actorList.push_back(new LittleRadiusLaser(std::move(sub)));
}
