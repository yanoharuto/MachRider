#include "Wheels.h"
#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "AssetManager.h"
//�����^�C���̏����p�x
static const float firstLWheelRota = 0.0f;
//�E���^�C���̏����p�x
static const float firstRWheelRota = 180.0f;
//�Ԃ̉�]��
static const float wheelDriveRotaPower = 4.4f;
//�^�C�������E�ɌX����
static const float wheelCurvePower = 1.7f;
//���̊p�x�܂Ń^�C���͌X����
static const float maxWheelRotaY = 45.5f;
//�i�s�����ɉe������܂łɕK�v�ȃ^�C���̊p�x
static const float rotaCalculationLine = 1.2f;

Wheels::Wheels(const WheelArgumentCarInfo InitInfo)
{
	carInfo = InitInfo;
	InitWheel(lFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(lBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(rBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
	InitWheel(rFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
}

Wheels::~Wheels()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(lFWheel.modelHandle);
	MV1DeleteModel(rFWheel.modelHandle);
	MV1DeleteModel(lBWheel.modelHandle);
	MV1DeleteModel(rBWheel.modelHandle);
}

void Wheels::Draw()
{
	MV1DrawModel(lFWheel.modelHandle);
	MV1DrawModel(rFWheel.modelHandle);
	MV1DrawModel(lBWheel.modelHandle);
	MV1DrawModel(rBWheel.modelHandle);
}

/// <summary>
/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
/// </summary>
/// <param name="_Key">���͏��</param>
void Wheels::WheelUpdate(const WheelArgumentCarInfo info)
{
	carInfo = info;
	AllSetWheelMatrix();
	//�Ԃ������Ƃ悭���
	if (carInfo.carSpeed > 0)
	{
		wheelDriveSpeed += -carInfo.carSpeed * wheelDriveRotaPower;
	}
	//�^�C�����X���鏈��
	if (UserInput::GetInputState(Right) != Free)
	{		
		isStraightDash = false;
		if (wheelDriveRota < maxWheelRotaY)
		{
			wheelDriveRota += wheelCurvePower;
		}
		else
		{
			wheelDriveRota = maxWheelRotaY;
		}

	}
	else if (UserInput::GetInputState(Left) != Free)
	{		
		isStraightDash = false;
		if (wheelDriveRota > -maxWheelRotaY)
		{
			wheelDriveRota -= wheelCurvePower;
		}
		else
		{
			wheelDriveRota = -maxWheelRotaY;
		}
	}
	//�ǂ�����������ĂȂ�������^�C�������ɖ߂�
	else if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		wheelDriveRota += wheelDriveRota > 0 ? -wheelCurvePower : wheelCurvePower;
		//������x�߂��Ă���p�x��0�ɂ���
		if (fabsf(wheelDriveRota) < rotaCalculationLine)
		{
			wheelDriveRota = 0;
		}
		isStraightDash = true;
	}	
}

/// <summary>
/// �ǂ̌����ɋȂ���΂������^���W�F���g��Ԃ���
/// </summary>
/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
/// <returns>���̐��Ȃ炾�����獶</returns>
float Wheels::GetMoveDirTheta(const float velocitySize)
{
	if (wheelDriveRota > rotaCalculationLine)
	{
		return atan2f(velocitySize, GetRotationRadius(firstLWheelRota)); 
	}
	else if (wheelDriveRota < -rotaCalculationLine)
	{
		return -atan2f(velocitySize,GetRotationRadius(firstLWheelRota));
	}
	return 0.0f;
}

void Wheels::AllSetWheelMatrix()
{
	//���O�^�C��
	SetWheelMatrix(lFWheel, wheelDriveSpeed, firstLWheelRota + wheelDriveRota);
	//�����^�C��
	SetWheelMatrix(lBWheel, wheelDriveSpeed, firstLWheelRota);
	//�E�O�^�C��	
	SetWheelMatrix(rFWheel, -wheelDriveSpeed, firstRWheelRota + wheelDriveRota);
	//�E���^�C��
	SetWheelMatrix(rBWheel, -wheelDriveSpeed, firstRWheelRota);
}
/// <summary>
/// ��]���邽�߂̔��a��Ԃ�
/// </summary>
/// <param name="firstWheelRota"></param>
/// <returns></returns>
float Wheels::GetRotationRadius(const float firstWheelRota)
{

	if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		//�^�C���̊p�x���^���W�F���g��
		float rota = tan(static_cast<float> (fabsf(wheelDriveRota)) * RAGE);
		//��]���a���o��
		float radius = (fWheelPos.x + bWheelPos.x) / rota;
		//�Ԃ̌����Ɍ��^�C����Y������]������
		VECTOR bWDir = VTransform(carInfo.direction, MGetRotY((firstWheelRota) * RAGE));
		//���^�C���̉��������o��
		bWDir = VNorm(VCross(bWDir, VGet(0, 1, 0)));
		//��]���a�̒��S���W���o��
		VECTOR circleAxisPos = VScale(bWDir, radius);

		//�i�s�������Ȃ���̂ɕK�v�ȉ~�̔��a���o��
		return  VSize(circleAxisPos);
	}
	return 0.0f;
}
/// <summary>
	/// �Ԃ��猩���^�C���̍��W���Ԃ��Ă���
	/// </summary>
	/// <param name="_wheel"></param>
VECTOR Wheels::WheelGetPos(const Wheel& wheel)
{
	//�^�C���̑O�������̈ʒu
	VECTOR between = VScale(carInfo.direction, -wheel.betweenBody.x);
	//�^�C���̉������̈ʒu�Ƒ���
	between = VAdd(between, VScale(VCross(carInfo.direction, VGet(0, 1, 0)), -wheel.betweenBody.z));
	//���������킹��
	between.y = fWheelPos.y;
	return  between;
}
/// <summary>
	/// �^�C���̈ʒu�Ɖ�]��ݒ�
	/// </summary>
	/// <param name="_wheel">�ݒ肵�����^�C��</param>
	/// <param name="_rotaX">�^�C���̓]����Ƃ��̉�]</param>
	/// <param name="_rotaY">�^�C���̌����������Ƃ��̉�]</param>

void Wheels::SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY)
{
	//�^�C���̈ʒu���Ԃ̌����ɍ��킹��
	MATRIX wheelPos = MMult(carInfo.matrix, MGetTranslate(WheelGetPos(wheel)));

	MATRIX wheelRota = MMult(MGetRotX(rotaX * RAGE), MGetRotY(rotaY * RAGE));
	wheel.matrix = MMult(wheelRota, wheelPos);
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}
/// <summary>
/// �^�C���̏�����
/// </summary>
/// <param name="_Wheel">�������������^�C��</param>
/// <param name="_ModelHandle">�^�C���̃��f��</param>
/// <param name="_Pos">�Ԃ��猩���ʒu</param>
/// <param name="_Rota">��]�p</param>
void Wheels::InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota)
{
	wheel.modelHandle = MV1DuplicateModel(DuplicateSourceModel);
	wheel.betweenBody = pos;
	VECTOR wheelPos = WheelGetPos(wheel);
	MATRIX bodyMat = MV1GetMatrix(DuplicateSourceModel);

	wheel.matrix = MMult(MGetRotY(rota * RAGE), MMult(bodyMat, MGetTranslate(wheelPos)));
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}