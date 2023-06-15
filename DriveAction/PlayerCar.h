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
	PlayerCar(VECTOR firstPos,VECTOR direction);
	///�f�X�g���N�^
    ~PlayerCar();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update() override;
	void GameReserve() override;
	void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;
private:
	/// <summary>
	/// �Ԃ���]������
	/// </summary>
	void ModelSetMatrix() const override;
	/// <summary>
	/// ���͂���Ƌ@�̂��X��
	/// </summary>
	void SetInputDir();
	/// <summary>
	/// �����Ă���Ƃ��̃G�t�F�N�g���X�V
	/// </summary>
	void EffectUpdate();
	/// <summary>
	/// �_���[�W���󂯂����̃��A�N�V����
	/// </summary>
	/// <param name="conflictInfo"></param>
	void DamageReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// �Ԃ��������̃��A�N�V����
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ConflictReaction(const ConflictExamineResultInfo conflictInfo);

	void DamagePostProccess();
	//����
	const float setFirstPosY = 6.0f;
	//�����Ă���Ƃ��ɏo��G�t�F�N�g
	int runEffect = -1;
	//�Ԃ��������ɏo�Ă���G�t�F�N�g
	int stageConflictEffect = -1;
	//�_���[�W���󂯂����̃G�t�F�N�g
	int damageEffect = -1;
	//�Ȃ������肷��Ƃ��ɌX�����x
	const float twistZRotaSpeed = 1.7f * RAGE;
	//�ő�X���x
	const float twistZMaxRota = 27.0f * RAGE;

	
	float upDownSpeed = 2.05f;
	float cosSeed = 0.01f;
	float totalCosSeed;
	//�c�ɉ�]����
	float twistZRota = 0.0f;
	//�_���[�W
	bool isDamage = false;
	//�_���[�W���󂯂����̑���s�\���Ԃ̍��v
	const float setDamageReactionTime = 0.5f;
	//�_���[�W���󂯂����ɉ�]���鑬�x
	const float damageReactionRotaSpeed = 75.0f;
	Timer* damageTimer;
};