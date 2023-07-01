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
	//�����ʒu�ݒ�
	firstPosY = position.y;
	position = firstPos;
	position.y = firstPosY;
	prevPos = position;
	direction = setDirection;
	//�G�t�F�N�g��ǂݍ��܂���
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
	if (turboEffect != -1)
	{
		StopEffekseer3DEffect(turboEffect);
		turboEffect = -2;
	}
	if (clashEffect != -1)
	{
		StopEffekseer3DEffect(clashEffect);
		clashEffect = -2;
	}
	if (damageEffect != -1)
	{
		StopEffekseer3DEffect(damageEffect);
		damageEffect = -2;
	}
	if (turboCourceEffect != -1)
	{
		StopEffekseer3DEffect(turboCourceEffect);
		turboCourceEffect = -2;
	}
	if (burnerEffect != -1)
	{
		StopEffekseer3DEffect(burnerEffect);
		burnerEffect = -2;
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
	if (conflictInfo.tag == stage)
	{

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
	else if(!isDamage) //�_���[�W���󂯂Ă��Ȃ��ău���[�L���ĂȂ��Ȃ����
	{
		float nextPower = accelPower + speedParamator.acceleSpeed;//������̑��x
		//������z������maxSpeed��
		accelPower = nextPower > speedParamator.maxSpeed ? speedParamator.maxSpeed : nextPower;
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
	//�_���[�W���󂯂Ă��Ȃ�������^�[�{
	float power = isDamage ? accelPower : accelPower + GetTurboPower();
	//�����x�N�g���𐶐�
	return VScale(direction, power);
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
	if (IsEffekseer3DEffectPlaying(clashEffect) == true)//�Ԃ��������̃G�t�F�N�g�����@�ɍ��킹��
	{
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
	}
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	
	if (isDamage)//�_���[�W���󂯂Ă�����
	{
		//�@�̂���o�鉊������
		if (burnerEffect != -1)
		{
			StopEffekseer3DEffect(burnerEffect);
			burnerEffect = -1;
		}
		//�X�s�[�h�o�Ă��Ȃ�������G�t�F�N�g������
		if (turboEffect != -1)
		{
			StopEffekseer3DEffect(turboEffect);
			turboEffect = -1;
		}
		//�^�[�{���Ă���Ƃ��ɏo��i�s�������o��
		if (turboCourceEffect != -1)
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
		}

	}
	else
	{
		if (isTurbo)//�}�������ɏo��G�t�F�N�g
		{
			UpdateEffe(&turboEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), carWind);
		}
		else
		{
			StopEffekseer3DEffect(turboEffect);
			turboEffect = -1;
		}
		//�^�[�{�������Ȃ�
		if (isTurboReserve)
		{
			UpdateEffe(&turboCourceEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), turboCourse);
		}
		else
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
		}
		//�����Ă���Ƃ��o��G�t�F�N�g
		UpdateEffe(&burnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), burner);
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
	SAFE_DELETE(collVecDecelTimer);
	collVecDecelTimer = new Timer(conflictInfo.bouncePower);
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
	SAFE_DELETE(collVecDecelTimer);
	collVecDecelTimer = new Timer(conflictInfo.bouncePower);
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
/// �G�t�F�N�g�̈ʒu�ƕ������Z�b�g
/// </summary>
/// <param name="playEffect"></param>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="effectKind"></param>
void PlayerCar::UpdateEffe(int* playEffect, VECTOR pos, VECTOR dir, EffectKind effectKind)
{
	//�G�t�F�N�g���o�ĂȂ�������o��
	if (*playEffect == -1 || IsEffekseer3DEffectPlaying(*playEffect))
	{
		*playEffect = EffectManager::GetPlayEffect3D(effectKind);
	}
	//�Ԃ̏ꏊ�ƌ����ɍ��킹��
	SetPosPlayingEffekseer3DEffect(*playEffect, pos.x, pos.y, pos.z);
	if (VCross(VGet(1, 0, 0), direction).y < 0)
	{
		SetRotationPlayingEffekseer3DEffect(*playEffect, dir.x, -dir.y, dir.z);
	}
	else
	{
		SetRotationPlayingEffekseer3DEffect(*playEffect, dir.x, dir.y, dir.z); 
	}
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