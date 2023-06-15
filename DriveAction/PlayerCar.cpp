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
	position.y = firstPosY;
	DamagePostProccess();
	//����������
	VECTOR accelVec = GetAccelVec();
	//���x���X�V
	UpdateVelocity(accelVec);
	//�ʒu�̍X�V
	ReflectsVelocity();
	//��]�Ƃ��𐧌�
	ModelSetMatrix();
	//�^�C���̍X�V
	WheelArgumentCarInfo carInfo;
	carInfo.Init(MV1GetMatrix(modelHandle), direction, VSize(velocity));
	wheels->WheelUpdate(carInfo);

	SetInputDir();
	SoundPlayer::SetListener(position, VAdd(position, direction));
	SoundPlayer::Play2DSE(playerFlight);
	EffectUpdate();

}

void PlayerCar::GameReserve()
{
	totalCosSeed += cosSeed;
	position.y = firstPosY + cosf(totalCosSeed) * upDownSpeed;
}

void PlayerCar::ConflictProccess(ConflictExamineResultInfo conflictInfo)
{
	if (conflictInfo.tag == damageObject)
	{
		DamageReaction(conflictInfo);
	}
	else if (conflictInfo.tag != collect)
	{
		ConflictReaction(conflictInfo);
	}
}

void PlayerCar::SetInputDir()
{
	//�E�����������Ă���
	if (UserInput::GetInputState(Right) == Hold)
	{
		twistZRota += twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		twistZRota -= twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Up) == Hold)
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	else//�Ȃɂ������Ă��Ȃ����̏���
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	//�Ȃ��鎞�̌X���̐���
	if (fabsf(twistZRota) > twistZMaxRota)
	{
		twistZRota = twistZRota > 0 ? twistZMaxRota : -twistZMaxRota;
	}
	if (UserInput::GetInputState(KeyInputKind::Down) == Hold)
	{
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
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	position = conflictInfo.pos;
	position.y = firstPosY;
	if (!isDamage)
	{
		damageEffect = EffectManager::GetPlayEffect3D(EffectInit::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage);
		isDamage = true;
		//���G���ԃZ�b�g
		damageTimer = new Timer(setDamageReactionTime);
		twistZRota = 0.0f;
	}
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
/// �@�̂���]������
/// </summary>
void PlayerCar::ModelSetMatrix() const
{
	float rota = 0;
	if (isDamage)
	{
		rota = damageTimer->GetLimitTime() / setDamageReactionTime * 100;
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