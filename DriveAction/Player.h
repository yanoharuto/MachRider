#pragma once
#include "DxLib.h"
#include "Racer.h"
class SphereCollider;
class ObjectSubject;
class Timer;
/// <summary>
/// �v���C���[�̎Ԃ�A�C�e���̏������Ăяo��
/// </summary>
class Player final:
    public Racer 
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos);
    ~Player();
    /// <summary>
    /// �v���C���[�̍X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObjGene"></param>
    void Update()override;
    /// <summary>
    /// �Ԃ̈ʒu�Ƃ���n��
    /// </summary>
    /// <returns></returns>
    ObjectSubject* GetSubject();
private:
    SphereCollider* collider;
    ObjectSubject* subject;
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