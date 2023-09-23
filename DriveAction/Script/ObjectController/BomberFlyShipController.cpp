#include "BomberFlyShipController.h"
#include "BomberFlyShip.h"
#include "DrawModel.h"
/// <summary>
/// �����@�̏������Ɣ��e���ˏ���
/// </summary>
/// <param name="generator">���e�𔭎˂ł���N���X</param>
BomberFlyShipController::BomberFlyShipController(std::shared_ptr<DamageObjectGenerator> generator)
    :FlyShipController(InitObjKind::bomberShip,generator)
{
    drawModel = new DrawModel(InitObjKind::bomberShip);
}
/// <summary>
/// �����@��ǉ�����
/// </summary>
/// <param name="editData">�z�u���</param>
void BomberFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(new BomberFlyShip(editData,param,damageObjectGenerator));
}
