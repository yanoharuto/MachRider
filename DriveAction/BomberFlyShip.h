#pragma once
#include "FlyShip.h"
#include "FlyShipController.h"
#include "EditObjectData.h"
#include <string>
class Timer;
class ReusableTimer;
/// <summary>
/// �����@
/// </summary>
class BomberFlyShip :
    public FlyShip
{
public:
    /// <summary>
    /// �����@
    /// </summary>
    /// <param name="setFirstPos">�o���ʒu</param>
    /// <param name="setDestinationPos">�ړI�n</param>
    BomberFlyShip(PlacementData data,FlyShipInit::InitFlyShipParamator initParam);
    /// <summary>
    /// ���e�𗎂Ƃ��Ȃ���i��
    /// </summary>
    void Update() override;
private:
    //���e�𗎂Ƃ�����
    ReusableTimer* bombFallTimer;
};

