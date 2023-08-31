#pragma once
#include "LaserFlyShip.h"
#include "EditObjectData.h"
/// <summary>
/// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
/// </summary>
class UpDownLaserFlyShip : public LaserFlyShip
{
public:
    /// <summary>
    /// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
    /// </summary>
    UpDownLaserFlyShip(PlacementData setPos);
    /// <summary>
    /// �㉺�ɓ�����
    /// </summary>
    void Update() override;
private:
    //totalMoveValue�̑�����
    static const float addMoveValue;
    //�㉺�ɓ������x
    static const float updownSpeed;
    //��������
    float totalMoveValue = 0;
};

