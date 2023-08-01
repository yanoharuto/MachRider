#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "ActorController.h"

class ObjectObserver;
/// <summary>
/// �_���[�W����̂���I�u�W�F�N�g�̑���e�N���X
/// </summary>
class DamageObjectController abstract:
    public ActorController
{
public:
    /// <summary>
    /// �_���[�W����̂���I�u�W�F�N�g
    /// </summary>
    /// <param name="kind"></param>
    DamageObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
    {};
    virtual void AddObject(std::unique_ptr<ObjectObserver> sub) = 0;
protected:
};

