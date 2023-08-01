#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
class UpDownFlyShipController :
    public FlyShipController
{
public:
    UpDownFlyShipController();
    void AddObject(EditArrangementData editData);
};

