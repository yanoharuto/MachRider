#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// �㉺�Ɉړ������s��
/// </summary>
class UpDownFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// �㉺�Ɉړ������s���̏�����
    /// </summary>
    UpDownFlyShipController();
protected:
    /// <summary>
    /// �ǉ�����
    /// </summary>
    /// <param name="editData">�z�u����ʒu�����</param>
    void AddObject(PlacementData editData)override;
};

