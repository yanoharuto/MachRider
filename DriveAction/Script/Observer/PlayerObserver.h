#pragma once
#include "ObjectObserver.h"
class PlayerCar;
/// <summary>
/// �v���C���[�̏���n�����
/// </summary>
class PlayerObserver :public ObjectObserver
{
public:
    /// <summary>
    /// �v���C���[�̏���n�����
    /// </summary>
    /// <param name="playerCar">�v���C���[</param>
    PlayerObserver(PlayerCar* playerCar);
    /// <summary>
    /// ���W�A�C�e��������������
    /// </summary>
    /// <returns></returns>
    int GetCollectCount();
private:
    //�v���C���[
    PlayerCar* subject;
};