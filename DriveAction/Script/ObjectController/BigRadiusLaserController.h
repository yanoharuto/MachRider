#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectObserver;
/// <summary>
/// y����]������肷�郌�[�U�[
/// </summary>
class BigRadiusLaserController : public DamageObjectController
{
public:
    /// <summary>
    /// ������
    /// </summary>
    BigRadiusLaserController();
    /// <summary>
    /// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
    /// </summary>
    /// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
};

