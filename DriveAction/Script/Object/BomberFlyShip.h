#pragma once
#include "Actor.h"
#include "FlyShipController.h"
#include "EditObjectData.h"
#include <string>
class Timer;
class ReusableTimer;
class DamageObjGenerator;
/// <summary>
/// �����@
/// </summary>
class BomberFlyShip : public Actor
{
public:
    /// <summary>
    /// �����̈ʒu�ɐ����@
    /// </summary>
    /// <param name="data">�����ʒu�ƌ������������\����</param>
    /// <param name="initParam">���e���˃N�[���^�C��������</param>
    /// <param name="damageObjGenerator">���e���˂ɕK�v�ȃN���X</param>
    BomberFlyShip(PlacementData data,FlyShipInit::InitFlyShipParamator initParam,std::shared_ptr<DamageObjectGenerator> damageObjGenerator);
    /// <summary>
    /// damageObjectGenerator�̊J��
    /// </summary>
    ~BomberFlyShip();
    /// <summary>
    /// ���e�𗎂Ƃ��Ȃ���i��
    /// </summary>
    void Update() override;
private:
    //���e�𗎂Ƃ�����
    ReusableTimer* bombFallTimer;
    //���e�𐶐�����̂ɕK�v�ȃN���X
    std::shared_ptr<DamageObjectGenerator> damageObjectGenerator;
};

