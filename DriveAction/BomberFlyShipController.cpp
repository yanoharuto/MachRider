#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
BomberFlyShipController::BomberFlyShipController()
    :FlyShipController(bomberShip)
{
}

void BomberFlyShipController::AddObject(std::vector<EditArrangementData> editData)
{
    if (!editData.empty())
    {
        for (int i = 0; i < editData.size(); i++)
        {
            //������ނȂ�ǉ�
            if (editData[i].objKind == controllObjKind)
            {
                actorList.push_back(new BomberFlyShip(editData[i], param));
            }
        }
    }
    
}
