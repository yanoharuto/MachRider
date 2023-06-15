#pragma once
#include "Actor.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "Wheels.h"


struct ConflictExamineResultInfo;
struct HitCheckExamineObjectInfo;
struct ObjInfo;
struct InputInfo;
class Timer;
class Wheels;

/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car abstract :public Actor
{
public:
	/// <summary>
	/// �����ʒu����p�Ƃ�
	/// </summary>
	/// <param name="firstPos"></param>
	/// <param name="firstDir"></param>
	/// <param name="destinationPos"></param>
	/// <param name="soundPlayer"></param>
	Car(ObjectInit::InitObjKind);
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update();
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	virtual void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;

	/// <summary>
	/// �ړ�����O�̃|�W�V������n��
	/// </summary>
	/// <returns></returns>
	HitCheckExamineObjectInfo GetHitCheckExamineInfo() override;

protected:
	/// <summary>
	/// �Ԃ��Ԃ��������̊֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	virtual void ConflictReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// �i�ޕ����Ƒ������X�V����
	/// </summary>
	/// <param name"deltaTime">�o�ߎ���</param>
	/// <param name="accelVec">���̍X�V�܂łɐi�ޕ����Ƒ���</param>
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// model�̕`��ꏊ���X�V
	/// </summary>
	void ReflectsVelocity() override;

	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <param name="handleDir">���͂��ꂽ����</param>
	/// <param name="outsideHitFlag">�R�[�X�̊O�ɂ��邩</param>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <param name="soundPlayer">�����o�����</param>
	/// <returns>�i�ޗ�</returns>
	VECTOR GetAccelVec();

	void InitParamater(ObjectInit::InitObjKind kind) override;
	struct SpeedParamator
	{
		//������
		float acceleSpeed;
		//�Œᑬ�x
		float lowestSpeed;
		//�ō����x
		float maxSpeed;
		//�}�������x
		float turboAddSpeed;
		//�}��������
		float turboTime;
		//�Ȃ����
		float gripPower;
		//�~�܂��
		float breakPower;
	};
	enum CarInitKind
	{
		//������
		acceleSpeed = 2,
		//�Œᑬ�x
		lowestSpeed = 5,
		//�ō����x
		maxSpeed = 8,
		//�}�������x
		turboSpeed = 11,
		//�}��������
		turboTime = 14,
		//�Ȃ����
		gripPower = 17,
		//�~�܂��
		breakePower = 20
	};
	//�Ԃ̃p�����[�^�[
	SpeedParamator speedParamator;
	//����
	float accelPower = 0;
	//�ŏ���Y���W
	float firstPosY = 0;
	//����
	float turboPower;
	// �Ȃɂ����Ȃ����̌���.
	static const float defaultDecel;
	// �O���b�v�̌���.
	static const float gripDecel;
	// ��Q���ɂԂ������Ƃ��̌�����.
	static const float colideDecel;
	//�^�C��
	Wheels* wheels;
	//�Ԃ��������̂Ƃ̕���
	VECTOR collVec = {};
	//�ЂƂO�̃|�W�V����
	VECTOR prevPos = {};
};
