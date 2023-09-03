#include "DemoCar.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
/// <summary>
/// �ʒu�Ȃǂ̏������ƃG�t�F�N�g�̃��[�h
/// </summary>
/// <param name="setPos">�����ʒu</param>
/// <param name="setDir">��������</param>
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
	EffectManager::LoadEffect(EffectInit::carWind);
	speedParamator.acceleSpeed = setAcceleSpeed;
	speedParamator.maxSpeed = setMaxSpeed;
}
/// <summary>
/// �^�C���ƃG�t�F�N�g�폜
/// </summary>
DemoCar::~DemoCar()
{
	SAFE_DELETE(wheels);

	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -1;
	}
}
/// <summary>
/// �����ʒu�ɖ߂�
/// </summary>
void DemoCar::InitPosition()
{
	position = firstPos;
}
/// <summary>
/// �X�V
/// </summary>
void DemoCar::Update()
{
	//���x���X�V
	UpdateVelocity();
	//�ʒu�̍X�V
	ReflectsVelocity();
	//�G�t�F�N�g�̍X�V
	EffectUpdate();
}
/// <summary>
/// �G�t�F�N�g�̍X�V
/// </summary>
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
/// <summary>/
/// ���鑬���x�N�g���̏���
/// </summary>
/// <returns></returns>
void DemoCar::UpdateAccelPower()
{
	// ��������.
	accelPower += speedParamator.acceleSpeed;
	if (accelPower > speedParamator.maxSpeed)
	{
		accelPower = speedParamator.maxSpeed;
	}
}