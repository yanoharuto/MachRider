#include "DemoCar.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
/// <summary>
/// 位置などの初期化とエフェクトのロード
/// </summary>
/// <param name="setPos">初期位置</param>
/// <param name="setDir">初期向き</param>
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
/// タイヤとエフェクト削除
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
/// 初期位置に戻す
/// </summary>
void DemoCar::InitPosition()
{
	position = firstPos;
}
/// <summary>
/// 更新
/// </summary>
void DemoCar::Update()
{
	//速度を更新
	UpdateVelocity();
	//位置の更新
	ReflectsVelocity();
	//エフェクトの更新
	EffectUpdate();
}
/// <summary>
/// エフェクトの更新
/// </summary>
void DemoCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//エフェクトが出てなかったら出す
	if (runEffect == -1)
	{
		//エフェクトが消えてたら出す
		runEffect = EffectManager::GetPlayEffect3D(EffectInit::carWind);
	}
	//車の場所と回転に合わせる
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
/// <summary>
/// 走る速さベクトルの所得
/// </summary>
/// <returns></returns>
VECTOR DemoCar::GetAccelVec()
{
	// 加速処理.
	accelPower += speedParamator.acceleSpeed;
	if (accelPower > speedParamator.maxSpeed)
	{
		accelPower = speedParamator.maxSpeed;
	}
	return VScale(direction, accelPower);
}
