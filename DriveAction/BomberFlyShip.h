#pragma once
#include "FlyShip.h"
#include "FlyShipCommander.h"
#include <string>
class Timer;
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
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos,FlyShipInit::InitFlyShipParamator initParam);
    /// <summary>
    /// ���e�𗎂Ƃ��Ȃ���i��
    /// </summary>
    void Update() override;
private:
    Timer* bombFallTimer;
    Timer* aliveTimer;
    //����
    static float speed;
};

