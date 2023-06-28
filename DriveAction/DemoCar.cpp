#include "DemoCar.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
DemoCar::DemoCar(VECTOR setPos, VECTOR setDir)
    :Car(ObjectInit::player)
{
	firstPosY = position.y;
	position = setPos;
	firstPos = setPos;
	position.y = firstPosY;
	prevPos = position;
	direction = setDir;
	firstDir = setDir;
	EffectManager::LoadEffect(EffectInit::carConflict);
	EffectManager::LoadEffect(EffectInit::carWind);
	EffectManager::LoadEffect(EffectInit::carDamage);
	speedParamator.acceleSpeed = 2;
	speedParamator.maxSpeed = 7;
}

DemoCar::~DemoCar()
{
	SAFE_DELETE(wheels);

	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -1;
	}
}

void DemoCar::InitPosition()
{
	position = firstPos;
}

void DemoCar::Update()
{
	//���x���X�V
	UpdateVelocity();
	//�ʒu�̍X�V
	ReflectsVelocity();
	//��]�Ƃ��𐧌�
	ModelSetMatrix();
	//�G�t�F�N�g�̍X�V
	EffectUpdate();
}

void DemoCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
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

VECTOR DemoCar::GetAccelVec()
{
	// ��������.
	accelPower += speedParamator.acceleSpeed;
	if (accelPower > speedParamator.maxSpeed)
	{
		accelPower = speedParamator.maxSpeed;
	}
	return VScale(direction, accelPower);
}
