#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "DrawModel.h"
/// <summary>
/// �����@�̊Ǘ��̏�����
/// </summary>
BomberFlyShipController::BomberFlyShipController()
    :FlyShipController(bomberShip)
{
    drawModel = new DrawModel(bomberShip);
}
/// <summary>
/// �����@��ǉ�����
/// </summary>
/// <param name="editData">�z�u���</param>
void BomberFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(new BomberFlyShip(editData, param));
}
