#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
/// </summary>
class UpDownLaserFlyShip :
    public LaserFlyShip
{
public:
    /// <summary>
    /// �㉺�ɓ����Ȃ��烌�[�U�[���o�����
    /// </summary>
    UpDownLaserFlyShip(VECTOR setPos);
    /// <summary>
    /// �㉺�ɓ�����
    /// </summary>
    void Update() override;
    /// <summary>
    /// ���[�U�[�𔭎�
    /// </summary>
    void GenerateLaser()override;
private:
    //Cos�̗�
    static const float addMoveValue;
    //�㉺�ɓ������x
    static const float updownSpeed;
    //��������
    float totalMoveValue = 0;
};

