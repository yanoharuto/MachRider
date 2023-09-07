#include "UpDownFlyShipController.h"
#include "UpDownLaserFlyShip.h"
#include "DrawModel.h" 
/// <summary>
/// �㉺�Ɉړ������s�D�̊Ǘ�����
/// </summary>
/// <param name="damageObjeGenerator">���[�U�[�𔭎˂ł���悤�ɂ���</param>
UpDownFlyShipController::UpDownFlyShipController(std::shared_ptr<DamageObjectGenerator> damageObjeGenerator)
    :FlyShipController(upDownLaserShip,damageObjeGenerator)
{
    drawModel = new DrawModel(upDownLaserShip);
}
/// <summary>
/// �㉺�ɑ΋󂷂��s�D�������̈ʒu�ɒǉ�
/// </summary>
/// <param name="editData">�z�u�ʒu</param>
void UpDownFlyShipController::AddObject(PlacementData editData)
{
    actorList.push_back(new UpDownLaserFlyShip(editData,damageObjectGenerator));
}