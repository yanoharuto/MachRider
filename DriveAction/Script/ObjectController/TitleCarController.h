#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class TitleCar;
class Timer;
class ObjectObserver;
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
class TitlteCarController : public ActorController
{
public:
    /// <summary>
    /// �^�C�g���ő��点���
    /// </summary>
    /// <param name="setPos">�����ʒu</param>
    /// <param name="setDir">��������</param>
    TitlteCarController(VECTOR setPos,VECTOR setDir);
    /// <summary>
    /// �����Ă���Ԃƕ`����̊J��
    /// </summary>
    ~TitlteCarController()override;
    /// <summary>
    /// �Ԃ̈ړ�
    /// </summary>
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()const override;
    /// <summary>
    /// �ʒu�̏�����
    /// </summary>
    void InitPosition();
    /// <summary>
    /// �Ԃ̈ʒu�Ȃǂ��J�����Ȃǂɓn����悤�ɂ���
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<ObjectObserver> CreateCarObserver();
private:
    //�^�C�g���ő����
    TitleCar* titleCar;
    //�Ԃ̈ʒu�Ȃǂ�`����
    std::shared_ptr<ObjectObserver> observer;
};