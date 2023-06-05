#pragma once
#include "FlyShipCommander.h"

class UpDownFlyShipCommander :
    public FlyShipCommander
{
public:
    UpDownFlyShipCommander(VECTOR firstPos);
    ~UpDownFlyShipCommander();
};

