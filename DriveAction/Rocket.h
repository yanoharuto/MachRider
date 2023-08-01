#pragma once
#include "DamageObject.h"
class SphereCollider;
class ConflictProcessor;
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
class Rocket final :public DamageObject
{
public:
    Rocket(std::unique_ptr<ObjectObserver> setObserver);
    ~Rocket() override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// �Փˌ�̏���
    /// </summary>
    void ConflictProcess(ConflictExamineResultInfo resultInfo)override;
private:
    //�ŏ��̗������x
    static const float setFallingSpeed;
    //�������x
    float fallingSpeed = setFallingSpeed;
    //�d��
    static const float gravityPower;
    //�R�������̓����蔻��̑傫��
    static const float setBurnRadius;
    //�R���Ă���Ƃ��̃G�t�F�N�g
    int burnEffect = -1;
    //�n�ʂɐG��Ă��邩
    bool onGround = false;
    //�����蔻��
    SphereCollider* collider = nullptr;
    //�Փˏ������s��
    ConflictProcessor* conflictProcessor;
};