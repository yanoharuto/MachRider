#pragma once
#include "LaserFlyShip.h"
/// <summary>
/// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
/// </summary>
class CircleLaserFlyShip :
    public LaserFlyShip
{
public:
    /// <summary>
    /// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// ���[�U�[�𔭎˂���
    /// </summary>
    void GenerateLaser() override;
private:
};

