#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "DrawModel.h"

UpDownFlyShipController::UpDownFlyShipController()
    :FlyShipController(upDownLaserShip)
{
    drawModel = new DrawModel(upDownLaserShip);
}

void UpDownFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(new UpDownLaserFlyShip(editData));
}