#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "ModelViewer.h"

UpDownFlyShipController::UpDownFlyShipController()
    :FlyShipController(upDownLaserShip)
{
    viewer = new ModelViewer(upDownLaserShip);
}

void UpDownFlyShipController::AddObject(EditArrangementData editData)
{
    FlyShip* flyShip = new UpDownLaserFlyShip(editData);
    actorList.push_back(flyShip);
}
