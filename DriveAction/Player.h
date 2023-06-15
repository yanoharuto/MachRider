#pragma once
#include <iostream>
#include<memory>
#include "DxLib.h"
#include "ActorController.h"
class SphereCollider;
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// �v���C���[�̎Ԃ�A�C�e���̏������Ăяo��
/// </summary>
class Player final:
    public ActorController
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos,VECTOR direction);
    /// <summary>
    /// �Ԃ̈ʒu�Ƃ���n��
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<ObjectObserver> CreatePlayerObserver() const;
    void GameReserve()override;
private:
    SphereCollider* collider;
    ObjectSubject* subject;
    std::shared_ptr <ObjectObserver> observer;
    const float setDamageCoolTime = 1.5f;
};

/// <summary>
/// �v���C���[��UI����ɕK�v�ȏ��
/// </summary>
enum PlayerRelatedInfo
{
    //����������
    damageObjHitCount = 0,
    //�R�C�������������
    hitCoinCount = 1,
    //���x
    accelPower = 3,
};