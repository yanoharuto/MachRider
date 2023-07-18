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
	//初期位置設定
	firstPosY = position.y;
	position = firstPos;
	position.y = firstPosY;
	prevPos = position;
	direction = setDirection;
	//エフェクトを読み込ませる
	EffectManager::LoadEffect(EffectInit::carConflict);
	EffectManager::LoadEffect(EffectInit::carWind);
	EffectManager::LoadEffect(EffectInit::carDamage);
	EffectManager::LoadEffect(EffectInit::turboCourse);
	EffectManager::LoadEffect(EffectInit::burner);
	EffectManager::LoadEffect(EffectInit::chargeBurner);
	EffectManager::LoadEffect(EffectInit::turboBurner);
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
	DeleteEffect(defaultBurnerEffect);
	DeleteEffect(turboBurnerEffect);
	DeleteEffect(turboCourceEffect);
	DeleteEffect(chargeBurnerEffect);
	DeleteEffect(damageEffect);
	DeleteEffect(clashEffect);
	DeleteEffect(windEffect);
}

/// <summary>
/// 更新
/// </summary>
void PlayerCar::Update()
{
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
	UpdateEffects();
	//連続してぶつかっているか調べる
	isSerialConflict = isConflictFlag;
	isConflictFlag = false;
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
	else if(!isDamage) //ダメージを受けていなくてブレーキしてないなら加速
	{
		float nextPower = accelPower + speedParamator.acceleSpeed;//加速後の速度
		//上限を越したらmaxSpeedに
		accelPower = nextPower > speedParamator.maxSpeed ? speedParamator.maxSpeed : nextPower;
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
	//ダメージを受けていなかったらターボ
	float power = isDamage ? accelPower : accelPower + GetTurboPower();
	//加速ベクトルを生成
	return VScale(direction, power);
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
void PlayerCar::UpdateEffects()
{
	if (IsEffekseer3DEffectPlaying(clashEffect) != -1)//ぶつかった時のエフェクトを自機の位置に合わせる
	{
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
	}
	//車の向き
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	
	if (isDamage)//ダメージを受けていたら
	{
		//機体から出る炎を消す
		if (defaultBurnerEffect != -1)
		{
			StopEffekseer3DEffect(defaultBurnerEffect);
			defaultBurnerEffect = -1;
		}
		//スピード出ていなかったらエフェクトを消す
		if (windEffect != -1)
		{
			StopEffekseer3DEffect(windEffect);
			windEffect = -1;
		}
		//ターボしているときに出る進行方向を出す
		if (turboCourceEffect != -1)
		{
			StopEffekseer3DEffect(turboCourceEffect);
			turboCourceEffect = -1;
		}

	}
	else
	{
		if (isTurbo)//急加速中に出るエフェクト
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
		//ターボ準備中なら
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
			//走っているとき出るエフェクト
			UpdateEffect(&defaultBurnerEffect, VAdd(position, VScale(direction, -radius)), VGet(-twistZRota, degree * RAGE, 0), burner);
		}
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
	SAFE_DELETE(collVecDecelTimer);
	collVecDecelTimer = new Timer(conflictInfo.bouncePower);
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
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
		isTurboReserve = false;
		SAFE_DELETE(turboTimer);
		//後ろの炎も消す
		DeleteEffect(chargeBurnerEffect);
		DeleteEffect(turboBurnerEffect);
		DeleteEffect(defaultBurnerEffect);
	}
}
/// <summary>
/// 衝突時のリアクション
/// </summary>
/// <param name="conflictInfo"></param>
void PlayerCar::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	//ターボ中で連続衝突していないなら
	if (isTurbo && !isSerialConflict)
	{
		//ぶつかった時の音とエフェクト
		clashEffect = EffectManager::GetPlayEffect3D(EffectInit::carConflict);
		SetPosPlayingEffekseer3DEffect(clashEffect, position.x, position.y, position.z);
		SoundPlayer::Play3DSE(playerDamage); SoundPlayer::Play3DSE(playerDamage);
	}
	isConflictFlag = true;

	//減速
	accelPower -= accelPower * colideDecel;

	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
	//エフェクトも移動
	UpdateEffects();
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
	//ダメージを受けていたら0
	if (isDamage)
	{
		isTurboReserve = false;
		isTurbo = false;
		return 0;
	}
	//下方向に入力するとターボ準備完了
	if (UserInput::GetInputState(Down) == Hold)
	{
		turboChargeTime += DELTATIME;
		//初めてターボ準備中
		if (!isTurboReserve)
		{
			isTurbo = false;
			//チャージ中バーナーに変更して終了
			StopEffekseer3DEffect(defaultBurnerEffect);
			chargeBurnerEffect = EffectManager::GetPlayEffect3D(chargeBurner);
			isTurboReserve = true;
		}
		return 0;
	}
	else if (UserInput::GetInputState(Down) == Detach)//離すとターボ
	{
		isTurboReserve = false;
		
		turboChargeTime = turboChargeTime > speedParamator.turboTime ? speedParamator.turboTime : turboChargeTime;
		turboTimer = new Timer(turboChargeTime);
		//初めて加速するときは
		if (!isTurbo)
		{
			isTurbo = true;
			StopEffekseer3DEffect(chargeBurnerEffect);
			turboBurnerEffect = EffectManager::GetPlayEffect3D(turboBurner);
		}
	}
	//ターボ期間中
	if (isTurbo)
	{
		if (turboTimer != nullptr && !turboTimer->IsOverLimitTime())//加速
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
/// エフェクトの位置と方向をセット
/// </summary>
/// <param name="playEffect"></param>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="effectKind"></param>
void PlayerCar::UpdateEffect(int* playEffect, VECTOR pos, VECTOR dir, EffectKind effectKind)
{
	//エフェクトが出てなかったら出す
	if (*playEffect == -1 || IsEffekseer3DEffectPlaying(*playEffect))
	{
		*playEffect = EffectManager::GetPlayEffect3D(effectKind);
	}
	//車の場所と向きに合わせる
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
/// エフェクトを消去
/// </summary>
/// <param name="effectHandle">消したいエフェクト</param>
void PlayerCar::DeleteEffect(int effectHandle)
{
	if (effectHandle != -1)
	{
		StopEffekseer3DEffect(effectHandle);
		effectHandle = -2;
	}
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