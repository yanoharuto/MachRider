#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
/// </summary>
class CircleFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
    /// </summary>
    CircleFlyShipController();
private:
    /// <summary>
    /// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
    /// </summary>
    void AddObject(PlacementData arrangementData);
};

