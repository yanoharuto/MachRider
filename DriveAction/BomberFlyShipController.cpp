#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "ModelViewer.h"
BomberFlyShipController::BomberFlyShipController()
    :FlyShipController(bomberShip)
{
    viewer = new ModelViewer(bomberShip);
}

void BomberFlyShipController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //“¯‚¶Ží—Þ‚È‚ç’Ç‰Á
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new BomberFlyShip(editData[i], param));
            }
        }
    }
}
