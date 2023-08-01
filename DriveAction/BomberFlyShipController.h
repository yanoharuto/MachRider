#pragma once
#include "FlyShipController.h"
class BomberFlyShipController :
    public FlyShipController
{
public:
    BomberFlyShipController();
    void AddObject(std::vector<EditArrangementData> editData)override;
};

