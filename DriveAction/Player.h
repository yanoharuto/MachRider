#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class SphereCollider;
class PlayerObserver;
class SoundListener;
class PlayerDrawModel;
class PlayerCar;
/// <summary>
/// �v���C���[�̎Ԃ̊Ǘ�
/// </summary>
class Player final:
    public ActorController
{
public:
    /// <summary>
    /// �v���C���[�̎Ԃ̊Ǘ�
    /// </summary>
    Player();
    /// <summary>
    /// �Ԃ�Lisner��Delete
    /// </summary>
    ~Player();
    /// <summary>
    /// �Ԃ̈ʒu�Ƃ���n��
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<PlayerObserver> CreatePlayerObserver() const;
    /// <summary>
    /// ���𕷂����߂ɏꏊ���X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() const override;
    /// <summary>
    /// �v���C���[�̓Q�[���I���܂œ���
    /// </summary>
    /// <returns></returns>
    bool IsAlive()const override { return true; };
private:
    //�v���C���[�̎Ԃ̓����蔻��
    SphereCollider* collider;
    //���삷���
    PlayerCar* car;
    //�`��Ɏg��
    PlayerDrawModel* playerDrawer;
    //���𕷂��ꏊ�̍X�V
    SoundListener* listener = nullptr;
    //�_���[�W���󂯂�N�[���^�C��
    const float setDamageCoolTime = 0.1f;
    std::shared_ptr<PlayerObserver> playerObserver;
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