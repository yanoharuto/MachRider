#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "DrawModel.h"

UpDownFlyShipController::UpDownFlyShipController()
    :FlyShipController(upDownLaserShip)
{
    drawModel = new DrawModel(upDownLaserShip);
}

void UpDownFlyShipController::AddObject(std::vector<PlacementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //������ނȂ�ǉ�
            if (editData[i].objKind == controllObjKind)
            {
                FlyShip* flyShip = new UpDownLaserFlyShip(editData[i]);
                actorList.push_back(flyShip);
            }
        }
    }
}
