#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class DemoCar;
class Timer;
class ObjectObserver;
/// <summary>
/// �^�C�g���ő��点��
/// </summary>
class DemoCarController : public ActorController
{
public:
    /// <summary>
    /// �^�C�g���ő��点���
    /// </summary>
    /// <param name="setPos">�����ʒu</param>
    /// <param name="setDir">��������</param>
    DemoCarController(VECTOR setPos,VECTOR setDir);
    /// <summary>
    /// �����Ă���Ԃƕ`����̊J��
    /// </summary>
    ~DemoCarController()override;
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
    DemoCar* demoCar;
    //�Ԃ̈ʒu�Ȃǂ�`����
    std::shared_ptr<ObjectObserver> observer;
};