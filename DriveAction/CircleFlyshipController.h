#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
/// </summary>
class CircleFlyShipController:
    public FlyShipController
{
public:
    /// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̍X�V�Ƃ�����
/// </summary>
    CircleFlyShipController();
    /// <summary>
    /// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̒ǉ�
    /// </summary>
    void AddObject(std::vector<EditArrangementData> arrangementData) override;
private:
    /// <summary>
/// �ւɂȂ��Ă��郌�[�U�[�Ǝˋ@�̔z�u�ƒǉ�
/// </summary>
    void AddObject(EditArrangementData arrangementData);
};

