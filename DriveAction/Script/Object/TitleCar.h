#pragma once
#include "Car.h"
/// <summary>
/// �^�C�g����ʂő��点���
/// </summary>
class TitleCar : public Car
{
public:
    /// <summary>
    /// �ʒu�Ȃǂ̏������ƃG�t�F�N�g�̃��[�h
    /// </summary>
    /// <param name="setPos">�����ʒu</param>
    /// <param name="setDir">��������</param>
    TitleCar(VECTOR setPos,VECTOR setDir);
    /// <summary>
    /// �^�C���ƃG�t�F�N�g���
    /// </summary>
    ~TitleCar()override;
    /// <summary>
    /// �����ʒu�ɖ߂�
    /// </summary>
    void InitPosition();
    /// <summary>
    /// �������ɑ���
    /// </summary>
    void Update()override;
private:
    /// <summary>
    /// �G�t�F�N�g�̍X�V
    /// </summary>
    void EffectUpdate();
    /// <summary>
    /// ���鑬���x�N�g���̏���
    /// </summary>
    /// <returns></returns>
    void UpdateAccelPower()override;
    //����G�t�F�N�g
    int runEffect = -1;
    //�����ʒu
    VECTOR firstPos;
    //��������
    VECTOR firstDir;
    //�����x
    const float setAcceleSpeed = 2;
    //�ő�l
    const float setMaxSpeed = 5;
};

