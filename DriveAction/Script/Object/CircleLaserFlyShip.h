#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
/// </summary>
class CircleLaserFlyShip : public LaserFlyShip
{
public:
    /// <summary>
    /// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// �`��ł���i�K�ɂȂ�����active�ɂȂ�
    /// </summary>
    void Update()override;
private:
};

