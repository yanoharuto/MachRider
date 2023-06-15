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
/// デストラクタ
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
/// 更新
/// </summary>
void PlayerCar::Update()
{
	position.y = firstPosY;
	DamagePostProccess();
	//速さを所得
	VECTOR accelVec = GetAccelVec();
	//速度を更新
	UpdateVelocity(accelVec);
	//位置の更新
	ReflectsVelocity();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤの更新
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
	//右か左か押してたら
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
	else//なにも押していない時の処理
	{
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	//曲がる時の傾きの制御
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
	//走っている最中に出るエフェクト ぶつかったら消える
	if (VSize(collVec) < 0.1f && isDamage == false)
	{
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
	else
	{
		//スピード出ていなかったらエフェクトを消す
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
		//無敵時間セット
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
	//減速
	accelPower -= accelPower * colideDecel;
	//衝突して移動
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
/// 機体を回転させる
/// </summary>
void PlayerCar::ModelSetMatrix() const
{
	float rota = 0;
	if (isDamage)
	{
		rota = damageTimer->GetLimitTime() / setDamageReactionTime * 100;
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