#pragma once
#include "DamageObject.h"
class SphereCollider;
class ConflictProcessor;
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
class Bomber final :public DamageObject
{
public:
    /// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
    Bomber(std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// �������蔻��폜
    /// </summary>
    ~Bomber() override;
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
    /// <summary>
    /// �����蔻��폜
    /// </summary>
    void EraceCollider();
    //�ŏ��̗������x
    static const float setFallingSpeed;
    //�������x
    float fallingSpeed = setFallingSpeed;
    //�d��
    static const float gravityPower;
    //�R���Ă���Ƃ��̃G�t�F�N�g
    int burnEffect = -1;
    //�����蔻��
    SphereCollider* collider = nullptr;
    //�Փˏ������s��
    ConflictProcessor* conflictProcessor;
};