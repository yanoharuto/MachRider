#include "Wheels.h"
#include "InputDirection.h"
#include "Car.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundPlayer.h"
#include "HitCheckExamineObjectInfo.h"
#include "ObjPosAndDir.h"
#include "Timer.h"

//これ以下の速度になってたらaccelPowerを0にするよ
const float Car:: lowestSpeed = 1.2f;
// なにもしない時の減速.
const float Car::defaultDecel = 0.01f;
// ブレーキ時の減速.
const float Car:: breakDecel = 0.03f;
// グリップの減速.
const float Car:: gripDecel = 0.08f;
// 障害物にぶつかったときの減速率.
const float Car:: colideDecel = 0.98f;
//ダメージを受けた時の操作不可能時間の合計
const float Car:: setDamageReactionTime = 0.5f;
//ダメージを受けた時に回転する速度
const float Car:: damageReactionRotaSpeed = 75.0f;

Car::Car()
{
	tag = ObjectTag::player;
	UpdatePosition();
	ModelSetMatrix();
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}
/// <summary>
/// 初期化
/// </summary>
/// <param name="param"></param>
Car::Car(CarInfomation param,ObjectInit::InitObjKind kind)
	:Actor(kind)
{
	tag = ObjectTag::player;
	carParam.gripPower = param.gripPower;
	carParam.addSpeed = param.addSpeed;
	carParam.maxSpeed = param.maxSpeed;
	UpdatePosition();
	ModelSetMatrix();
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

}

Car::~Car()
{
	SAFE_DELETE(wheels);
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
	if (conflictInfo.tag == damageObject)
	{
		DamageReaction(conflictInfo);
	}
	else if (conflictInfo.tag != coin)
	{
		ConflictReaction(conflictInfo);
	}
}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;
	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// 車がダメージ判定のある物体にぶつかった時の関数
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	isDamage = true;
	damageReactionTime = setDamageReactionTime;
	//無敵時間セット
	twistZRota = 0.0f;
}
/// <summary>
/// 車がダメージを受けた後に走る処理
/// </summary>
/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
void Car::PostDamageProccess()
{
	//ダメージを受けたならダメージを受けたリアクションをする
	if (isDamage)
	{
		damageReactionTime -= DELTATIME;
		if (damageReactionTime < 0)
		{
			isDamage = false;
		}
	}
}

/// <summary>
/// 進む方向と速さを更新する
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <param name="accelVec">次の更新までに進む方向と速さ</param>
void Car::UpdateVelocity(const VECTOR accelVec)
{
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	theta *= carParam.gripPower - (carParam.gripPower  * GetTotalAccelPowerPercent()) / 100;
	velocity = VTransform(accelVec, MGetRotY(theta));
	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::UpdatePosition()
{
	//更新する前のポジションを保存
	prevPos = position;
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	//ぶつかった時の衝撃で移動
	if (VSize(collVec) > 0.1f)
	{
		position = VAdd(position, collVec);
		collVec = VScale(collVec, defaultDecel);
	}
	else //衝撃が無くなったら運転できる
	{
		// ポジションを更新.
		position = VAdd(position, velocity);
	}
}
/// <summary>
/// 車を回転させる
/// </summary>
void Car::ModelSetMatrix() const
{
	float rota = 0;
	if (isDamage)
	{
		rota = damageReactionTime / setDamageReactionTime * 100;
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
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void Car::AutoDrive()
{
	CommonUpdate();
}
/// <summary>
/// 共通処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="destinationPos"></param>
/// <param name="itemInfo"></param>
void Car::CommonUpdate()
{
	//落下
	UpDown();
	//ダメージを受けている時は
	PostDamageProccess();
	//速さを所得
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir);
	//速度を更新
	UpdateVelocity(accelVec);

	//位置の更新
	UpdatePosition();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤに渡したい情報を出す
	InitWheelArgumentCarInfo();
	//タイヤの更新
	wheels->WheelUpdate(wheelArgumentCarInfo);
}


VECTOR Car::GetAccelVec(InputInfo inputDir )
{
	float decelPower = 0;
	//ブレーキしてなかったら
	if (!inputDir.isBreake)
	{
		// 加速処理.
		accelPower += carParam.addSpeed;

		accelPower += turboPower;
		turboPower = turboPower > 0 ? turboPower - turboPower * defaultDecel : 0;
		if (accelPower > carParam.maxSpeed)
		{
			accelPower = carParam.maxSpeed;
		}
	}
		//左右に曲がろうとしていたら減速
	if (inputDir.handleDir != HandleDirection::straight)
	{
		//左右に曲がろうとしたら減速する
		decelPower = gripDecel;
		if (inputDir.isBreake)
		{
			turboPower = turboPower > 3 ? 3 : turboPower + carParam.addSpeed;

		}
	}

	//ブレーキしていたら減速
	if (inputDir.isBreake)
	{
		decelPower = breakDecel;
	}
	accelPower -= accelPower * decelPower;
	
	//最低速度
	if (accelPower < lowestSpeed)
	{
		accelPower = lowestSpeed;
	}
	return VScale(direction, accelPower);
}


/// <summary>
/// タイヤに渡す情報の初期化
/// </summary>
void Car::InitWheelArgumentCarInfo()
{
	wheelArgumentCarInfo.matrix = MV1GetMatrix(modelHandle);
	wheelArgumentCarInfo.direction = direction;
	wheelArgumentCarInfo.velocitySize = VSize(velocity);
}
/// <summary>
/// 上下に動く
/// </summary>
/// <param name="deltaTime"></param>
void Car::UpDown()
{
	position.y = firstPosY + cos(cosValue) * updownSpeed;
	cosValue += cosAddValue;
}

/// <summary>
/// 今の速度は最大速度の何割なのか所得出来る
/// </summary>
/// <returns></returns>
float Car::GetTotalAccelPowerPercent()
{
	return (accelPower) / (carParam.maxSpeed ) * 100;
}

float Car::GetTotalAccelPower()
{
	return accelPower ;
}

/// <summary>
/// 移動する前のポジションを渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Car::GetHitCheckExamineInfo()
{
	HitCheckExamineObjectInfo info;
	info.pos = prevPos;
	info.radius = radius;
	info.velocity = velocity;
	return info;
}
