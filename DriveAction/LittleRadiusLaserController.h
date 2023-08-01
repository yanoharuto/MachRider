#pragma once
#include <vector>
#include "DamageObjectController.h"
class ObjectObserver;
/// <summary>
/// ������y����]���郌�[�U�[�̍X�V��
/// </summary>
class LittleRadiusLaserController :
    public DamageObjectController
{
public:
    /// <summary>
/// ������y����]���郌�[�U�[�̍X�V��
/// </summary>
    LittleRadiusLaserController()
        :DamageObjectController(ObjectInit::littleRadiusLaser)
    {};
    /// <summary>
    /// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
    /// </summary>
    /// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
    void AddObject(std::unique_ptr<ObjectObserver> sub)override;
private:
};