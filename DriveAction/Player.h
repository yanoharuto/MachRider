#pragma once
#include <iostream>
#include<memory>
#include "DxLib.h"
#include "ActorController.h"
class SphereCollider;
class ObjectSubject;
class ObjectObserver;
class SoundListener;
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
    ~Player();
    /// <summary>
    /// �Ԃ̈ʒu�Ƃ���n��
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<ObjectObserver> CreatePlayerObserver() const;
    /// <summary>
    /// ���𕷂����߂ɏꏊ���X�V
    /// </summary>
    void Update()override;
private:
    SphereCollider* collider;
    std::shared_ptr<ObjectObserver> subject;

    //���𕷂��ꏊ�̍X�V
    SoundListener* listener = nullptr;

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