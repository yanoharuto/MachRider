#pragma once
#include "FlyShip.h"

/// <summary>
/// ���[�U�[���o����s�D
/// </summary>
class LaserFlyShip abstract:
    public FlyShip
{
public:
    /// <summary>
    /// ������ �ړI�n�̕��Ɍ�������
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos,ObjectInit::InitObjKind kind);
    /// <summary>
    /// ���[�U�[���Ǝ�
    /// </summary>
    virtual void GenerateLaser() = 0;
protected:
    //�����ʒuY
    float firstPosY;
};
