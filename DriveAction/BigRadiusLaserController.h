#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectObserver;
/// <summary>
/// y����]������肷�郌�[�U�[
/// </summary>
class BigRadiusLaserController :
    public DamageObjectController
{
public:

    /// <summary>
    /// y����]������肷�郌�[�U�[
    /// </summary>
    BigRadiusLaserController() 
        :DamageObjectController(ObjectInit::bigRadiusLaser)
    {};
    /// <summary>
/// ���[�U�[���Ǝ˂����I�u�W�F�N�g�������ɂ��炤
/// </summary>
/// <param name="sub">���[�U�[���Ǝ˂����I�u�W�F�N�g</param>
    void AddObject(std::unique_ptr<ObjectObserver> sub)override;
private:
};

