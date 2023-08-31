#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "ActorController.h"

class ObjectObserver;
/// <summary>
/// �_���[�W����̂���I�u�W�F�N�g�̊Ǘ��N���X
/// </summary>
class DamageObjectController abstract : public ActorController
{
public:
    /// <summary>
    /// �_���[�W����̂���I�u�W�F�N�g�̊Ǘ��N���X
    /// </summary>
    /// <param name="kind">������������</param>
    DamageObjectController(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �����̃I�u�W�F�N�g���琶�����ꂽ�Ƃ�
    /// </summary>
    /// <param name="sub">���˂����I�u�W�F�N�g�̈ʒu������Ȃǂ�n���N���X</param>
    virtual void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub) = 0;
};

