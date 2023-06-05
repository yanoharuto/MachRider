#pragma once
#include "Car.h"
class SphereCollider;
class Wheels;
 /// <summary>
 /// �v���C���[(��)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	PlayerCar(VECTOR firstPos);
	///�f�X�g���N�^
    ~PlayerCar();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update() override;

private:
	//���͂ɂ���đ��������ς���
	void SetInputDir();
	void EffectUpdate();
	void DamageReaction(const ConflictExamineResultInfo conflictInfo) override;
	void ConflictReaction(const ConflictExamineResultInfo conflictInfo) override;
	//����
	const float setFirstPosY = 6.0f;

	static const CarInfomation setCarParam;

	//�����Ă���Ƃ��ɏo��G�t�F�N�g
	int runEffect = -1;
	//�Ԃ��������ɏo�Ă���G�t�F�N�g
	int stageConflictEffect = -1;
	//�_���[�W���󂯂����̃G�t�F�N�g
	int damageEffect = -1;
};