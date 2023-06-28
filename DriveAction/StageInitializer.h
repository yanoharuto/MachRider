#pragma once
#include <iostream>
#include <memory>
#include "StageDataPass.h"
class ActorControllerManager;
class ObjectObserver;

/// <summary>
/// �X�e�[�W�̏�����
/// </summary>
class StageInitializer :StageDataPass
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageInitializer();
    ~StageInitializer();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="cotrollerManager"></param>
    void Init(ActorControllerManager* cotrollerManager);
    /// <summary>
    /// �v���C���[�̈ʒu���������Ă�������o��
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<ObjectObserver> GetPlayerObserver()const;
    /// <summary>
    /// �X�e�[�W�̐�������
    /// </summary>
    /// <returns></returns>
    float GetGameTime()const;
private:
    //�v���C���[�̈ʒu���������Ă������
    std::weak_ptr<ObjectObserver> playerObserver;
};