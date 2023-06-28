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
/// デストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_DELETE(wheels);
	SAFE_DELETE(damageTimer);
	SAFE_DELETE(turboTimer);
	
	SoundPlayer::StopSound(playerFlight);
	SoundPlayer::StopSound(playerDamage);
	//まだエフェクトが出ていたら終了
	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		runEffect = -2;
	}
}

/// <summary>
/// 更新
/// </summary>
void PlayerCar::Update()
{
	position.y = firstPosY;
	//ダメージを受けてたら無敵時間減少していく
	DamagePostProccess();
	//速度を更新
	UpdateVelocity();
	//位置の更新
	ReflectsVelocity();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤの更新
	WheelArgumentCarInfo carInfo;
	carInfo.Init(MV1GetMatrix(modelHandle), direction, VSize(velocity));
	wheels->WheelUpdate(carInfo);
	//機体を傾ける
	SetTwistZRota();
	//空を飛んでいるときの音をループ再生
	if (!SoundPlayer::IsPlaySound(playerFlight))
	{
		SoundPlayer::Play2DSE(playerFlight);
	}
	EffectUpdate();
}
/// <summary>
/// ゲームが始まる前の演出とか
/// </summary>
void PlayerCar::GameReserve()
{
	totalCosSeed += cosSeed;
	position.y = firstPosY + cosf(totalCosSeed) * upDownSpeed;
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictProccess(ConflictExamineResultInfo conflictInfo)
{
	if (conflictInfo.tag == damageObject)//ダメージを受けた
	{
		DamageReaction(conflictInfo);
	}
	else if (conflictInfo.tag != collect)//ぶつかった
	{
		ConflictReaction(conflictInfo);
	}
}
/// <summary>
/// 加速用ベクトルを作る
/// </summary>
/// <returns></returns>
VECTOR PlayerCar::GetAccelVec()
{
	//ブレーキした
	if (UserInput::GetInputState(Down) == InputState::Hold)
	{
		accelPower -= accelPower * speedParamator.breakPower;
	}
	else//してないなら加速
	{
		accelPower += speedParamator.acceleSpeed;
		if (accelPower > speedParamator.maxSpeed)//上限
		{
			accelPower = speedParamator.maxSpeed;
		}
	}
	//左右に曲がろうとしていたら減速
	if (UserInput::GetInputState(Left) == InputState::Hold && UserInput::GetInputState(Right) == InputState::Hold)
	{
		//左右に曲がろうとしたら減速する
		accelPower -= accelPower * gripDecel;
	}
	//最低速度
	if (accelPower < speedParamator.lowestSpeed)
	{
		accelPower = speedParamator.lowestSpeed;
	}
	
	//加速ベクトルを生成
	return VScale(direction, accelPower + GetTurboPower());
}
/// <summary>
/// 入力すると機体が傾く
/// </summary>
void PlayerCar::SetTwistZRota()
{
	//右か左か押してたら機体を傾ける
	if (UserInput::GetInputState(Right) == Hold)
	{
		twistZRota = twistZRota + twistZRotaSpeed > twistZMaxRota ? twistZMaxRota : twistZRota + twistZRotaSpeed;//上限値を越しそうならMaxRotaをセット
	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		twistZRota = twistZRota - twistZRotaSpeed < -twistZMaxRota? -twistZMaxRota : twistZRota - twistZRotaSpeed;
	}
	//何もしていない時や上下ボタンを押しているときは機体を水平に戻す
	else
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
/// <summary>
/// エフェクトの更新
/// </summary>
void PlayerCar::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//走っている最中に出るエフェクト ぶつかったら消える
	if (isTurbo && !isDamage)
	{
		//エフェクトが出てなかったら出す
		if (runEffect == -1)
		{
			runEffect = EffectManager::GetPlayEffect3D(EffectInit::carWind);
		}
		//車の場所と向きに合わせる
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
		//スピード出ていなかったらエフェクトを消す
		if (runEffect != -1)
		{
			StopEffekseer3DEffect(runEffect);
			runEffect = -1;
		}
	}
	if (isTurboReserve)
	{
		//エフェクトが出てなかったら出す
		if (turboCourceEffect == -1||IsEffekseer3DEffectPlaying(turboCourceEffect))
		{
			turboCourceEffect = EffectManager::GetPlayEffect3D(EffectInit::turboCourse);
		}
		//車の場所と向きに合わせる
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

	//エフェクトが出てなかったら出す
	if (burnerEffect == -1 || IsEffekseer3DEffectPlaying(burnerEffect))
	{
		burnerEffect = EffectManager::GetPlayEffect3D(EffectInit::burner);
	}
	VECTOR burnerPos = VAdd(position, VScale(direction, -radius));
	//車の場所と向きに合わせる
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
/// ダメージを与えた時のリアクション
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	//位置と吹っ飛びベクトルを取ってくる
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	position = conflictInfo.pos;
	position.y = firstPosY;
	if (!isDamage)
	{
		//ダメージを受けた時のエフェクトと音
		damageEffect = EffectManager::GetPlayEffect3D(EffectInit::carDamage);
		SetPosPlayingEffekseer3DEffect(damageEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage);
		isDamage = true;
		//無敵時間セット
		damageTimer = new Timer(setDamageReactionTime);
		twistZRota = 0.0f;
		//加速も終了
		isTurbo = false;
	}
}
/// <summary>
/// 衝突時のリアクション
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	//ぶつかった時の音とエフェクト
	int effect = EffectManager::GetPlayEffect3D(EffectInit::carConflict);
	SetPosPlayingEffekseer3DEffect(effect,position.x,position.y,position.z);
	SoundPlayer::Play3DSE(playerDamage);
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;
	//加速も終了
	isTurbo = false;
	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;

	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// ダメージ処理
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
/// 左右に押しながら下を離すとブースト
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
	//一度入力した方向と下方向に入力するとターボ準備完了
	if (UserInput::GetInputState(turboKey) == Hold && UserInput::GetInputState(Down) == Hold)
	{
		isTurboReserve = true;
	}

	//ターボ準備完了した状態でした方向を離すとターボ
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
	//ターボ期間中ずっとターボ
	if (isTurbo)
	{
		if (!turboTimer->IsOverLimitTime())
		{
			return turboTimer->GetRemainingTime() * speedParamator.turboAddSpeed;
		}
		else//終了後
		{
			isTurbo = false;
			turboChargeTime = 0;
			SAFE_DELETE(turboTimer);
		}
	}
	return 0;
}


/// <summary>
/// 機体を回転させる
/// </summary>
void PlayerCar::ModelSetMatrix() const
{
	float rota = 0;
	//ダメージを受けたら回転する
	if (isDamage)
	{
		rota = damageTimer->GetElaspedTime() / setDamageReactionTime * 100;
		rota *= damageReactionRotaSpeed;
	}
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), twistZRota);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + rota) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}