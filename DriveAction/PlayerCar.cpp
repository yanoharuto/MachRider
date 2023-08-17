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
#include "PlayerViewer.h"
#include "Timer.h"
#include "PlayerConflictProcessor.h"
#include "ConflictManager.h"
#include "SphereCollider.h"
/// <summary>
/// �v���C���[�����삷���
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDirection"></param>
PlayerCar::PlayerCar(EditArrangementData arrangementData)
	:Car(ObjectInit::player)
{
	//�����ʒu�ݒ�
	firstPosY = position.y;
	position.x = arrangementData.posX;
	position.z = arrangementData.posZ;
	position.y = firstPosY;
	prevPos = position;
	direction = VGet(arrangementData.dirX,0,arrangementData.dirZ);
	//�G�t�F�N�g��ǂݍ��܂���
	EffectManager::LoadEffect(EffectInit::carConflict);
	EffectManager::LoadEffect(EffectInit::carWind);
	EffectManager::LoadEffect(EffectInit::carDamage);
	EffectManager::LoadEffect(EffectInit::turboCourse);
	EffectManager::LoadEffect(EffectInit::burner);
	EffectManager::LoadEffect(EffectInit::chargeBurner);
	EffectManager::LoadEffect(EffectInit::turboBurner);
	//����ǂݍ��܂���
	SoundPlayer::LoadSound(playerFlight);
	SoundPlayer::LoadSound(playerCharge);
	SoundPlayer::LoadSound(playerDamage);
	//�Փˏ����Ăі�
	conflictProcessor = new PlayerConflictProcessor(this);
	hitChecker = new SphereCollider(this);
	ConflictManager::AddConflictProcessor(conflictProcessor,hitChecker);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_DELETE(wheels);
	SAFE_DELETE(bounceTimer);
	SAFE_DELETE(turboTimer);
	//�����蔻�����
	ConflictManager::EraceConflictProccesor(conflictProcessor, hitChecker);
	SAFE_DELETE(conflictProcessor);
	SAFE_DELETE(hitChecker);
	//������
	SoundPlayer::StopSound(playerFlight);
	SoundPlayer::StopSound(playerDamage);
	//�܂��G�t�F�N�g���o�Ă�����I��
	DeleteEffect(defaultBurnerEffect);
	DeleteEffect(turboBurnerEffect);
	DeleteEffect(turboCourceEffect);
	DeleteEffect(chargeBurnerEffect);
	DeleteEffect(damageEffect);
	DeleteEffect(clashEffect);
	DeleteEffect(windEffect);
}

/// <summary>
/// �X�V
/// </summary>
void PlayerCar::Update()
{	
	//�@�̂��X����
	RotateUpdate();
	//�_���[�W���󂯂Ă��疳�G���Ԍ������Ă���
	DamagePostProccess();
	//���x���X�V
	UpdateVelocity();
	//�ʒu�̍X�V
	ReflectsVelocity();
	//�^�C���̍X�V
	WheelArgumentCarInfo carInfo;
	carInfo.Init(MGetTranslate(position), direction, VSize(velocity));
	wheels->WheelUpdate(carInfo);
	UpdateEffects();
	//�A�����ĂԂ����Ă�����Serial��true�ɂȂ����܂�
	isSerialConflict = isNowConflict;
	isNowConflict = false;
}

/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictProcess(ConflictExamineResultInfo conflictInfo)
{
	if (conflictInfo.hit == HitSituation::Enter)
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
}
/// <summary>
/// �@�̂̌X����n��
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetModelRotateVec()
{
	//y����]
	float rotaY = 0;
	//�_���[�W���󂯂Ă����炮�邮���]
	if (isDamage)
	{
		rotaY = bounceTimer->GetElaspedTime() / setDamageReactionTime;
		rotaY *= damageReactionRotaValue;
	}

	return VGet(0,rotaY,twistZRota);
}

/// <summary>
/// ���W�A�C�e���ɂԂ�������
/// </summary>
/// <returns></returns>
int PlayerCar::GetCollectCount()
{
	return conflictProcessor->GetCollectNum();
}
/// <summary>
/// �����p�x�N�g�������
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetAccelVec()
{
	VECTOR accelVec = Car::GetAccelVec();
	//�_���[�W���󂯂Ă��Ȃ�������^�[�{
	if (!isDamage)
	{
		accelVec = VAdd(accelVec, VScale(direction, GetTurboPower()));
	}
	//�����x�N�g���𐶐�
	return accelVec;
}
/// <summary>
/// ���͂���Ƌ@�̂��X��
/// </summary>
void PlayerCar::RotateUpdate()
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
void PlayerCar::UpdateEffects()
{
	if (IsEffekseer3DEffectPlaying(clashEffect) != -1)//�Ԃ��������̃G�t�F�N�g�����@�̈ʒu�ɍ��킹��
	{
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
	}
	//�Ԃ̌���
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	
	if (isDamage)//�_���[�W���󂯂Ă�����
	{
		//�@�̂���o�鉊������
		if (defaultBurnerEffect != -1)
		{
			StopEffekseer3DEffect(defaultBurnerEffect);
			defaultBurnerEffect = -1;
		}
		//�X�s�[�h�o�Ă��Ȃ�������G�t�F�N�g������
		if (windEffect != -1)
		{
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
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
			UpdateEffect(&windEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), carWind);
			UpdateEffect(&turboBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), turboBurner);
		}
		else
		{
			StopEffekseer3DEffect(turboBurnerEffect);
			turboBurnerEffect = -1;
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//�^�[�{�������Ȃ�
		if (isTurboReserve)
		{
			UpdateEffect(&turboCourceEffect, VGet(position.x, 0, position.z), VGet(0, degree * RAGE, 0), turboCourse);
			UpdateEffect(&chargeBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), chargeBurner);
		}
		else
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
			StopEffekseer3DEffect(chargeBurnerEffect);
			chargeBurnerEffect = -1;
		}
		if (!(isTurbo || isTurboReserve))
		{
			//�����Ă���Ƃ��o��G�t�F�N�g
			UpdateEffect(&defaultBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), burner);
		}
	}
	
}
/// <summary>
/// �_���[�W��^�������̃��A�N�V����
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::DamageReaction(ConflictExamineResultInfo conflictInfo)
{
	//�ʒu�Ɛ�����уx�N�g��������Ă���
	conflictVec = VScale(conflictInfo.bounceVec,conflictInfo.bouncePower);
	conflictVec.y = 0;
	SAFE_DELETE(bounceTimer);
	//������Ԏ���
	bounceTimer = new Timer(setDamageReactionTime);
	
	position = conflictInfo.pos;
	position.y = firstPosY;
	
	if (!isDamage)
	{
		//�_���[�W���󂯂����̃G�t�F�N�g�Ɖ�
		damageEffect = EffectManager::GetPlayEffect3D(EffectInit::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage);
		isDamage = true;
		twistZRota = 0.0f;
		//�������I��
		isTurbo = false;
		isTurboReserve = false;
		SAFE_DELETE(turboTimer);
		//���̉�������
		DeleteEffect(chargeBurnerEffect);
		DeleteEffect(turboBurnerEffect);
		DeleteEffect(defaultBurnerEffect);
	}
}
/// <summary>
/// �Փˎ��̃��A�N�V����
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictReaction(ConflictExamineResultInfo conflictInfo)
{
	//�^�[�{���ŘA���Փ˂��Ă��Ȃ��Ȃ�
	if (isTurbo && !isSerialConflict)
	{
		//�Ԃ��������̉��ƃG�t�F�N�g
		clashEffect = EffectManager::GetPlayEffect3D(EffectInit::carConflict);
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage); 
	}
	isNowConflict = true;

	//����
	accelPower -= accelPower * colideDecel;

	//�Փ˂��Ĉړ�
	position = conflictInfo.pos;
	position.y = firstPosY;
	
	//�G�t�F�N�g���ړ�
	UpdateEffects();
}
/// <summary>
/// �_���[�W����
/// </summary>
void PlayerCar::DamagePostProccess()
{
	//�_���[�W���󂯂���
	if (isDamage)
	{
		//�_���[�W�^�C�}�[���؂��܂Ŗ��G
		if (bounceTimer->IsOverLimitTime())
		{
			isDamage = false;
			SAFE_DELETE(bounceTimer);
		}
	}
}
/// <summary>
/// ���E�ɉ����Ȃ��牺�𗣂��ƃu�[�X�g
/// </summary>
/// <returns></returns>
float PlayerCar::GetTurboPower()
{
	//�W���C�p�b�h��������Ή��{�^����ύX
	InputState turboInput = UserInput::GetInputState(Down);
	if (GetJoypadNum() != 0)
	{
		turboInput = UserInput::GetInputState(Space);
	}
	//�������ɓ��͂���ƃ^�[�{��������
	if (turboInput == Hold && ! isTurbo)
	{
		turboChargeTime += DELTATIME;
		//���߂ă^�[�{������
		if (!isTurboReserve)
		{
			//�`���[�W���o�[�i�[�ɕύX���ďI��
			StopEffekseer3DEffect(defaultBurnerEffect);
			chargeBurnerEffect = EffectManager::GetPlayEffect3D(chargeBurner);
			isTurboReserve = true;
			SoundPlayer::Play3DSE(playerCharge);
		}
		return 0;
	}
	//��������`���[�W�I��
	else 
	{	
		if (turboInput)
		{
			//�\���Ƀ`���[�W�o������^�[�{�ɓ���
			if (!isTurbo && turboChargeTime > speedParamator.turboChargeTime)
			{
				//���̃^�C�}�[�̊ԋ}����
				turboTimer = new Timer(speedParamator.turboTime);
				isTurbo = true;
				//��������Ƃ��̓G�t�F�N�g�Ɖ�������
				StopEffekseer3DEffect(chargeBurnerEffect);
				turboBurnerEffect = EffectManager::GetPlayEffect3D(turboBurner);
				SoundPlayer::Play3DSE(playerFlight);
			}
			isTurboReserve = false;
			turboChargeTime = 0;
			SoundPlayer::StopSound(playerCharge);
		}
	}
	//�^�[�{���Ԓ�
	if (isTurbo)
	{
		//����
		if (turboTimer != nullptr && !turboTimer->IsOverLimitTime())
		{
			//�����ʂ�n��
			return turboTimer->GetRemainingTime() * speedParamator.turboAddSpeed;
		}
		else//�I����
		{
			isTurbo = false;
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
void PlayerCar::UpdateEffect(int* playEffect, VECTOR pos, VECTOR dir, EffectKind effectKind)
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
/// �G�t�F�N�g������
/// </summary>
/// <param name="effectHandle">���������G�t�F�N�g</param>
void PlayerCar::DeleteEffect(int effectHandle)
{
	if (effectHandle != -1)
	{
		StopEffekseer3DEffect(effectHandle);
		effectHandle = -2;
	}
}