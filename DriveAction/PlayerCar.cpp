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
const CarInfomation PlayerCar::setCarParam =
{
	1.0f,
	10.0f,
	3.0f,
	0.13f,
	1.0f,
	0.34f,
	7.0f,
};

PlayerCar::PlayerCar(VECTOR firstPos)
	:Car(setCarParam,ObjectInit::player)
{
	firstPosY = position.y;
	position = firstPos;
	position.y = firstPosY;

	prevPos = position;
	direction = VGet(0.0f, 0.0f, -1.0f);
	SoundPlayer::SetListener(position,VAdd(position,direction));

	EffectManager::LoadEffect(EffectInit::carConflict);
	EffectManager::LoadEffect(EffectInit::carWind);
	EffectManager::LoadEffect(EffectInit::carDamage);
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

	SoundPlayer::StopSound(playerFlight);
	SoundPlayer::StopSound(playerDamage);

	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -1;
	}
}

/// <summary>
/// �X�V
/// </summary>
void PlayerCar::Update()
{
	SoundPlayer::Play2DSE(playerFlight);
	SetInputDir();
	CommonUpdate();
	SoundPlayer::SetListener(position, VAdd(position, direction));
	ArgumentConflictResultInfo resultInfo = GetConflictArgumentInfo();
	resultInfo.pos = position;
	VECTOR damageEffectPos = position;
	EffectUpdate();
	UpdatePosition();
#ifdef _DEBUG
	printfDx("position::%f,%f,%f\n", position.x,position.y,position.z);
	printfDx("dir::%f,%f,%f\n", direction.x,direction.y,direction.z);
	printfDx("velocity::%f,%f,%f\n", velocity.x,velocity.y,velocity.z);
#endif
}

void PlayerCar::SetInputDir()
{
	wheelArgumentCarInfo.inputDir.isBreake = false;
	//�E�����������Ă���
	if (UserInput::GetInputState(Right) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::right;
		twistZRota += twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::left;
		twistZRota -= twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Up) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	else//�Ȃɂ������Ă��Ȃ����̏���
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	//�Ȃ��鎞�̌X���̐���
	if (fabsf(twistZRota) > twistZMaxRota)
	{
		twistZRota = twistZRota > 0 ? twistZMaxRota : -twistZMaxRota;
	}
	if (UserInput::GetInputState(KeyInputKind::Down) == Hold)
	{
		wheelArgumentCarInfo.inputDir.isBreake = true;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
void PlayerCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//�����Ă���Œ��ɏo��G�t�F�N�g �Ԃ������������
	if (VSize(collVec) < 0.1f && isDamage == false)
	{
		//�G�t�F�N�g���o�ĂȂ�������o��
		if (runEffect == -1)
		{
			//�G�t�F�N�g�������Ă���o��
			runEffect = EffectManager::GetPlayEffect3D(EffectInit::carWind);
		}
		//�Ԃ̏ꏊ�Ɖ�]�ɍ��킹��
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
}

void PlayerCar::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	damageEffect = EffectManager::GetPlayEffect3D(EffectInit::carDamage);
	SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
	SoundPlayer::Play3DSE(playerDamage);
	isDamage = true;
	damageReactionTime = setDamageReactionTime;
	//���G���ԃZ�b�g
	twistZRota = 0.0f;
}

void PlayerCar::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	int effect = EffectManager::GetPlayEffect3D(EffectInit::carConflict);
	SetPosPlayingEffekseer3DEffect(effect,position.x,position.y,position.z);
	SoundPlayer::Play3DSE(playerDamage);
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//����
	accelPower -= accelPower * colideDecel;
	//�Փ˂��Ĉړ�
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
}