#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class SphereHitChecker;
class PlayerObserver;
class SoundListener;
class PlayerDrawModel;
class PlayerCar;
/// <summary>
/// �v���C���[�̎Ԃ̊Ǘ�
/// </summary>
class PlayerCarController final : public ActorController
{
public:
    /// <summary>
    /// �v���C���[�̎Ԃ̏�����
    /// </summary>
    PlayerCarController();
    /// <summary>
    /// �Ԃ�Lisner��Delete
    /// </summary>
    ~PlayerCarController();
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
private:
    //�v���C���[�̎Ԃ̓����蔻��
    SphereHitChecker* collider;
    //���삷���
    PlayerCar* car;
    //�`��Ɏg��
    PlayerDrawModel* playerDrawer;
    //���𕷂��ꏊ�̍X�V
    SoundListener* listener = nullptr;
    //�_���[�W���󂯂�N�[���^�C��
    const float setDamageCoolTime = 0.1f;
    //�v���C���[�̏������L���邽�߂̃|�C���^
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