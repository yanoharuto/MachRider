#pragma once
#include "Car.h"
#include "UserInput.h"
class SphereCollider;

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
    ~PlayerCar()override;
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update() override;
	/// <summary>
	/// �Q�[�����n�܂�O�̉��o�Ƃ�
	/// </summary>
	void GameReserve() override;
	/// <summary>
	/// �Ԃ��������̏���
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;
private:
	/// <summary>
	/// �����p�x�N�g�������
	/// </summary>
	/// <returns></returns>
	VECTOR GetAccelVec()override;
	/// <summary>
	/// �Ԃ���]������
	/// </summary>
	void ModelSetMatrix() const override;
	/// <summary>
	/// ���͂����TwistZRota���ύX����
	/// </summary>
	void SetTwistZRota();
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
	/// <summary>
	/// �_���[�W���󂯂���̏����B���G���ԕ��A�Ȃ�
	/// </summary>
	void DamagePostProccess();
	/// <summary>
	/// ���E�ɉ����Ȃ��牺�𗣂��ƃu�[�X�g
	/// </summary>
	/// <returns></returns>
	float GetTurboPower();
	//����
	const float setFirstPosY = 6.0f;
	//�����Ă���Ƃ��ɏo��G�t�F�N�g
	int runEffect = -1;
	//�}������
	bool isTurbo = false;
	//�}����������
	bool isTurboReserve = false;
	//�����`���[�W�^�C��
	float turboChargeTime;
	KeyInputKind turboKey;
	//�Ԃ��������ɏo�Ă���G�t�F�N�g
	int stageConflictEffect = -1;
	//�_���[�W���󂯂����̃G�t�F�N�g
	int damageEffect = -1;
	//�^�[�{�������ɏo��G�t�F�N�g
	int turboCourceEffect = -1;
	//���̉�
	int burnerEffect = -1;
	//�Ȃ������肷��Ƃ��ɌX�����x
	const float twistZRotaSpeed = 1.7f * RAGE;
	//�ő�X���x
	const float twistZMaxRota = 27.0f * RAGE;
	//�㉺�Ɉړ����鑬�x
	float upDownSpeed = 2.05f;
	//totalCosSeed�𑝉������������
	float cosSeed = 0.01f;
	//upDownSpeed��cosSeed�ɂ���ĕϓ�����
	float totalCosSeed;
	//�c�ɉ�]����
	float twistZRota = 0.0f;
	//�_���[�W
	bool isDamage = false;
	//�_���[�W���󂯂����̑���s�\���Ԃ̍��v
	const float setDamageReactionTime = 1.0f;
	//�_���[�W���󂯂����ɉ�]���鑬�x
	const float damageReactionRotaSpeed = 15.0f;
	//���G���Ԃ̃^�C�}�[
	Timer* damageTimer = nullptr;
	//�^�[�{����
	Timer* turboTimer = nullptr;
};