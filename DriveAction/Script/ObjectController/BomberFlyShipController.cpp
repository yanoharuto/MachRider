#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "DrawModel.h"
/// <summary>
/// 爆撃機の管理の初期化
/// </summary>
BomberFlyShipController::BomberFlyShipController()
    :FlyShipController(bomberShip)
{
    drawModel = new DrawModel(bomberShip);
}
/// <summary>
/// 爆撃機を追加する
/// </summary>
/// <param name="editData">配置情報</param>
void BomberFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(new BomberFlyShip(editData, param));
}
