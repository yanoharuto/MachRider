#include "UpDownFlyShipCommander.h"
#include "UpDownLaserFlyShip.h"

UpDownFlyShipCommander::UpDownFlyShipCommander(VECTOR firstPos)
{
    FlyShip* flyShip = new UpDownLaserFlyShip(firstPos);
    actorList.push_back(flyShip);
}
UpDownFlyShipCommander::~UpDownFlyShipCommander()
{
}
