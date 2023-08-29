#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "DrawModel.h"
BomberFlyShipController::BomberFlyShipController()
    :FlyShipController(bomberShip)
{
    drawModel = new DrawModel(bomberShip);
}

void BomberFlyShipController::AddObject(std::vector<PlacementData> editData)
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
