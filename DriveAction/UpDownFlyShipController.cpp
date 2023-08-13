#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "ModelViewer.h"

UpDownFlyShipController::UpDownFlyShipController()
    :FlyShipController(upDownLaserShip)
{
    viewer = new ModelViewer(upDownLaserShip);
}

void UpDownFlyShipController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //“¯‚¶Ží—Þ‚È‚ç’Ç‰Á
            if (editData[i].objKind == controllObjKind)
            {
                FlyShip* flyShip = new UpDownLaserFlyShip(editData[i]);
                actorList.push_back(flyShip);
            }
        }
    }
}
