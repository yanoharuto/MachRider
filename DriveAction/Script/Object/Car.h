#pragma once
#include "Actor.h"
#include "DxLib.h"
struct CollisionResultInfo;
struct HitCheckInfo;
class Timer;
class Wheels;
/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car abstract :public Actor
{
public:
	/// <summary>
	/// ��
	/// </summary>
	/// <param name="kind"> �~�����I�u�W�F�N�g�̎��</param>
	Car(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �^�C���̊J��
    /// </summary>
    virtual ~Car();
protected:
	/// <summary>
	/// �Ԃ��Ԃ��������̊֐�
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������̌���</param>
	virtual void ConflictReaction(const CollisionResultInfo conflictInfo);
	/// <summary>
	/// �i�ޕ����Ƒ������X�V����
	/// </summary>
	virtual void UpdateVelocity();
	/// <summary>
	/// model�̕`��ꏊ���X�V
	/// </summary>
	void ReflectsVelocity() override;
	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <returns>�i�ޗ�</returns>
	virtual void UpdateAccelPower();
	/// <summary>
	/// �ړ����x�Ȃǂ̏�����
	/// </summary>
	/// <param name="kind">���̎Ԃ̎��</param>
	void InitSpeedParamater(ObjectInit::InitObjKind kind);
	//�X�s�[�h�̃p�����[�^
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
		//�}�����ɕK�v�Ȏ���
		float turboChargeTime;
	};
	//�Ԃ̏������̎��
	enum class CarInitKind
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
		breakePower = 20,
		//�}�����ɕK�v�Ȏ���
		turboChargeTime = 23
	};
	//�Փ˂��Đ�����Ԏ��Ԃ��v��
	Timer* bounceTimer = nullptr;
	//�^�C��
	Wheels* wheels;
	//�Ԃ��������̂Ƃ̕���
	VECTOR conflictVec = {};
	//�ЂƂO�̃|�W�V����
	VECTOR prevPos = {};
	//�Ԃ̃p�����[�^�[
	SpeedParamator speedParamator;
	//����
	float accelPower = 0;
	//�ŏ���Y���W
	float firstPosY = 0;
	// �Ȃɂ����Ȃ����̌���.
	static const float defaultDecel;
	// �O���b�v�̌���.
	static const float gripDecel;
	// ��Q���ɂԂ������Ƃ��̌�����.
	static const float colideDecel;
	//�_���[�W
	bool isBounce = false;
};