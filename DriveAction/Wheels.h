#pragma once
#include "DxLib.h"
#include <string>
/// <summary>
/// �^�C�����������Ă�����
/// </summary>
struct Wheel
{
	int modelHandle = -1;//Duplicate����̂Ŗ{�͕̂�
	VECTOR betweenBody = {};//�Ԃ܂ł̋���
	MATRIX matrix;
};
/// <summary>
/// �^�C���Ɉ����œn���Ăق����Ԃ̏��
/// </summary>
struct WheelArgumentCarInfo
{
	MATRIX matrix;//�Ԃ�model�̍s��
	VECTOR direction;//�Ԃ̌���
	float carSpeed;//�����̑傫��

	void Init(MATRIX setM, VECTOR setDir, float setSpeed)
	{
		matrix = setM;
		direction = setDir;
		carSpeed = setSpeed;
	}
};

/// <summary>
/// �Ԃ����������n����B���ƃ^�C������]������`�悷��
/// </summary>
class Wheels 
{
public:
    Wheels(const WheelArgumentCarInfo InitInfo);
    ~Wheels();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

	/// <summary>
	/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
	/// </summary>
	/// <param name="_Key">���͏��</param>
	void WheelUpdate(const WheelArgumentCarInfo info);

	/// <summary>
	/// �ǂ̌����ɋȂ���΂������^���W�F���g��Ԃ���
	/// </summary>
	/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
	/// <returns>���̐��Ȃ炾�����獶</returns>
	float GetMoveDirTheta(const float velocitySize);
private:	

	/// <summary>
	/// �S�Ẵ^�C���̃}�g���b�N�X���Z�b�g����
	/// </summary>
	void AllSetWheelMatrix();
	/// <summary>
    /// ��]���邽�߂̔��a��Ԃ�
    /// </summary>
    /// <param name="firstWheelRota"></param>
    /// <returns></returns>
	float GetRotationRadius(const float firstWheelRota);
	/// <summary>
    /// �Ԃ��猩���^�C���̍��W���Ԃ��Ă���
    /// </summary>
    /// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
    /// �^�C���̈ʒu�Ɖ�]��ݒ�
    /// </summary>
    /// <param name="_wheel">�ݒ肵�����^�C��</param>
    /// <param name="_rotaX">�^�C���̓]����Ƃ��̉�]</param>
    /// <param name="_rotaY">�^�C���̌����������Ƃ��̉�]</param>
	void SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY);
	/// <summary>
	/// �^�C���̏�����
	/// </summary>
	/// <param name="_Wheel">�������������^�C��</param>
	/// <param name="_ModelHandle">�^�C���̃��f��</param>
	/// <param name="_Pos">�Ԃ��猩���ʒu</param>
	/// <param name="_Rota">��]�p</param>
	void InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota);
	
	//�Ԃ̉�]���x
	float wheelDriveSpeed = 0.0f;
	//�Ԃ̍��E�ւ̌X��
	float wheelDriveRota = 0.0f;
	//�܂������i��ł��邩�ǂ���
	bool isStraightDash;

	//�^�C���̃��f���n���h��
	int modelHandle;
	//���O���^�C��
	Wheel lFWheel;
	//������^�C��
	Wheel lBWheel;
	//�E�O���^�C��
	Wheel rFWheel;
	//�E����^�C��
	Wheel rBWheel;
	//�Ԃ̏��
	WheelArgumentCarInfo carInfo;
	VECTOR wheelEffectPos;
	const VECTOR fWheelPos = { 6.1f,0.8f,2.8f };
	const VECTOR bWheelPos = { 3.8f,0.8f,2.8f };
};