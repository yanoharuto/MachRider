#pragma once
#include "FlyShipController.h"
/// <summary>
/// �����@�Ǘ��N���X
/// </summary>
class BomberFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// �����@�̊Ǘ��̏�����
    /// </summary>
    BomberFlyShipController();
    /// <summary>
    /// �����@��ǉ�����
    /// </summary>
    /// <param name="editData">�z�u���</param>
    void AddObject(PlacementData editData)override;
};

