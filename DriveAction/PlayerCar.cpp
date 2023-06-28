#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
#include "SoundPlayer.h"
#include "EffectManager.h"
#include "ConflictManager.h"
#include "AssetManager.h"
#include "SphereCollider.h"

PlayerCar::PlayerCar(VECTOR firstPos,VECTOR setDirection)
	:Car(ObjectInit::player)
{
	firstPosY = position.y;
	position = firstPos;
	position.y = firstPosY;
	prevPos = position;
	direction = setDirection;

	EffectManager::LoadEffect(EffectInit::carConflict);
	EffectManager::LoadEffect(EffectInit::carWind);
	EffectManager::LoadEffect(EffectInit::carDamage);
	EffectManager::LoadEffect(EffectInit::turboCourse);
	EffectManager::LoadEffect(EffectInit::burner);
	SoundPlayer::LoadSound(playerFlight);
	SoundPlayer::LoadSound(playerDamage);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_DELETE(wheels);
	SAFE_DELETE(damageTimer);
	SAFE_DELETE(turboTimer);
	
	SoundPlayer::StopSound(playerFlight);
	SoundPlayer::StopSound(playerDamage);
	//�܂��G�t�F�N�g���o�Ă�����I��
	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -2;
	}
}

/// <summary>
/// �X�V
/// </summary>
void PlayerCar::Update()
{
	position.y = firstPosY;
	//�_���[�W���󂯂Ă��疳�G���Ԍ������Ă���
	DamagePostProccess();
	//���x���X�V
	UpdateVelocity();
	//�ʒu�̍X�V
	ReflectsVelocity();
	//��]�Ƃ��𐧌�
	ModelSetMatrix();
	//�^�C���̍X�V
	WheelArgumentCarInfo carInfo;
	carInfo.Init(MV1GetMatrix(modelHandle), direction, VSize(velocity));
	wheels->WheelUpdate(carInfo);
	//�@�̂��X����
	SetTwistZRota();
	//�����ł���Ƃ��̉������[�v�Đ�
	if (!SoundPlayer::IsPlaySound(playerFlight))
	{
		SoundPlayer::Play2DSE(playerFlight);
	}
	EffectUpdate();
}
/// <summary>
/// �Q�[�����n�܂�O�̉��o�Ƃ�
/// </summary>
void PlayerCar::GameReserve()
{
	totalCosSeed += cosSeed;
	position.y = firstPosY + cosf(totalCosSeed) * upDownSpeed;
}
/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictProccess(ConflictExamineResultInfo conflictInfo)
{
	if (conflictInfo.tag == damageObject)//�_���[�W���󂯂�
	{
		DamageReaction(conflictInfo);
	}
	else if (conflictInfo.tag != collect)//�Ԃ�����
	{
		ConflictReaction(conflictInfo);
	}
}
/// <summary>
/// �����p�x�N�g�������
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetAccelVec()
{
	//�u���[�L����
	if (UserInput::GetInputState(Down) == InputState::Hold)
	{
		accelPower -= accelPower * speedParamator.breakPower;
	}
	else//���ĂȂ��Ȃ����
	{
		accelPower += speedParamator.acceleSpeed;
		if (accelPower > speedParamator.maxSpeed)//���
		{
			accelPower = speedParamator.maxSpeed;
		}
	}
	//���E�ɋȂ��낤�Ƃ��Ă����猸��
	if (UserInput::GetInputState(Left) == InputState::Hold && UserInput::GetInputState(Right) == InputState::Hold)
	{
		//���E�ɋȂ��낤�Ƃ����猸������
		accelPower -= accelPower * gripDecel;
	}
	//�Œᑬ�x
	if (accelPower < speedParamator.lowestSpeed)
	{
		accelPower = speedParamator.lowestSpeed;
	}
	
	//�����x�N�g���𐶐�
	return VScale(direction, accelPower + GetTurboPower());
}
/// <summary>
/// ���͂���Ƌ@�̂��X��
/// </summary>
void PlayerCar::SetTwistZRota()
{
	//�E�����������Ă���@�̂��X����
	if (UserInput::GetInputState(Right) == Hold)
	{
		twistZRota = twistZRota + twistZRotaSpeed > twistZMaxRota ? twistZMaxRota : twistZRota + twistZRotaSpeed;//����l���z�������Ȃ�MaxRota���Z�b�g
	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		twistZRota = twistZRota - twistZRotaSpeed < -twistZMaxRota? -twistZMaxRota : twistZRota - twistZRotaSpeed;
	}
	//�������Ă��Ȃ�����㉺�{�^���������Ă���Ƃ��͋@�̂𐅕��ɖ߂�
	else
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
void PlayerCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//�����Ă���Œ��ɏo��G�t�F�N�g �Ԃ������������
	if (isTurbo && !isDamage)
	{
		//�G�t�F�N�g���o�ĂȂ�������o��
		if (runEffect == -1)
		{
			runEffect = EffectManager::GetPlayEffect3D(EffectInit::carWind);
		}
		//�Ԃ̏ꏊ�ƌ����ɍ��킹��
		SetPosPlayingEffekseer3DEffect(runEffect, position.x, 0, position.z);
		if (VCross(VGet(1, 0, 0), direction).y < 0)
		{
			SetRotationPlayingEffekseer3DEffect(runEffect, 0, -degree * RAGE, 0);
		}
		else
		{
			SetRotationPlayingEffekseer3DEffect(runEffect, 0, degree * RAGE, 0);
		}
	}
	else
	{
		//�X�s�[�h�o�Ă��Ȃ�������G�t�F�N�g������
		if (runEffect != -1)
		{
			StopEffekseer3DEffect(runEffect);
			runEffect = -1;
		}
	}
	if (isTurboReserve)
	{
		//�G�t�F�N�g���o�ĂȂ�������o��
		if (turboCourceEffect == -1||IsEffekseer3DEffectPlaying(turboCourceEffect))
		{
			turboCourceEffect = EffectManager::GetPlayEffect3D(EffectInit::turboCourse);
		}
		//�Ԃ̏ꏊ�ƌ����ɍ��킹��
		SetPosPlayingEffekseer3DEffect(turboCourceEffect, position.x, 0, position.z);
		if (VCross(VGet(1, 0, 0), direction).y < 0)
		{
			SetRotationPlayingEffekseer3DEffect(turboCourceEffect, 0, -degree * RAGE, 0);
		}
		else
		{
			SetRotationPlayingEffekseer3DEffect(turboCourceEffect, 0, degree * RAGE, 0);
		}
	}

	//�G�t�F�N�g���o�ĂȂ�������o��
	if (burnerEffect == -1 || IsEffekseer3DEffectPlaying(burnerEffect))
	{
		burnerEffect = EffectManager::GetPlayEffect3D(EffectInit::burner);
	}
	VECTOR burnerPos = VAdd(position, VScale(direction, -radius));
	//�Ԃ̏ꏊ�ƌ����ɍ��킹��
	SetPosPlayingEffekseer3DEffect(burnerEffect, burnerPos.x, burnerPos.y, burnerPos.z);
	if (VCross(VGet(1, 0, 0), direction).y < 0)
	{
		SetRotationPlayingEffekseer3DEffect(burnerEffect, -twistZRota, -degree * RAGE, 0);
	}
	else
	{
		SetRotationPlayingEffekseer3DEffect(burnerEffect, -twistZRota, degree * RAGE, 0);
	}

}
/// <summary>
/// �_���[�W��^�������̃��A�N�V����
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	//�ʒu�Ɛ�����уx�N�g��������Ă���
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	position = conflictInfo.pos;
	position.y = firstPosY;
	if (!isDamage)
	{
		//�_���[�W���󂯂����̃G�t�F�N�g�Ɖ�
		damageEffect = EffectManager::GetPlayEffect3D(EffectInit::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage);
		isDamage = true;
		//���G���ԃZ�b�g
		damageTimer = new Timer(setDamageReactionTime);
		twistZRota = 0.0f;
		//�������I��
		isTurbo = false;
	}
}
/// <summary>
/// �Փˎ��̃��A�N�V����
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	//�Ԃ��������̉��ƃG�t�F�N�g
	int effect = EffectManager::GetPlayEffect3D(EffectInit::carConflict);
	SetPosPlayingEffekseer3DEffect(effect,position.x,position.y,position.z);
	SoundPlayer::Play3DSE(playerDamage);
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//����
	accelPower -= accelPower * colideDecel;
	//�������I��
	isTurbo = false;
	//�Փ˂��Ĉړ�
	position = conflictInfo.pos;
	position.y = firstPosY;

	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// �_���[�W����
/// </summary>
void PlayerCar::DamagePostProccess()
{
	if (isDamage)
	{
		if (damageTimer->IsOverLimitTime())
		{
			isDamage = false;
			SAFE_DELETE(damageTimer);
		}
	}
}
/// <summary>
/// ���E�ɉ����Ȃ��牺�𗣂��ƃu�[�X�g
/// </summary>
/// <returns></returns>
float PlayerCar::GetTurboPower()
{
	if (UserInput::GetInputState(Left) == Push)
	{
		turboKey = Left;
		isTurboReserve = false;
	}
	else if (UserInput::GetInputState(Right) == Push)
	{
		turboKey = Right;
		isTurboReserve = false;
	}
	//��x���͂��������Ɖ������ɓ��͂���ƃ^�[�{��������
	if (UserInput::GetInputState(turboKey) == Hold && UserInput::GetInputState(Down) == Hold)
	{
		isTurboReserve = true;
	}

	//�^�[�{��������������Ԃł��������𗣂��ƃ^�[�{
	if (isTurboReserve)
	{
		turboChargeTime += DELTATIME;
		if (UserInput::GetInputState(Down) == Detach)
		{
			isTurboReserve = false;
			isTurbo = true;
			turboChargeTime = turboChargeTime > speedParamator.turboTime ? speedParamator.turboTime : turboChargeTime;
			turboTimer = new Timer(turboChargeTime);
		}
	}
	//�^�[�{���Ԓ������ƃ^�[�{
	if (isTurbo)
	{
		if (!turboTimer->IsOverLimitTime())
		{
			return turboTimer->GetRemainingTime() * speedParamator.turboAddSpeed;
		}
		else//�I����
		{
			isTurbo = false;
			turboChargeTime = 0;
			SAFE_DELETE(turboTimer);
		}
	}
	return 0;
}


/// <summary>
/// �@�̂���]������
/// </summary>
void PlayerCar::ModelSetMatrix() const
{
	float rota = 0;
	//�_���[�W���󂯂����]����
	if (isDamage)
	{
		rota = damageTimer->GetElaspedTime() / setDamageReactionTime * 100;
		rota *= damageReactionRotaSpeed;
	}
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), twistZRota);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + rota) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}