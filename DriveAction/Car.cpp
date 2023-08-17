#include "Wheels.h"
#include "Car.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundPlayer.h"
#include "HitCheckExamineObjectInfo.h"
#include "UserInput.h"
#include "Timer.h"
#include "InitActor.h"
#include "CSVFileLoader.h"

// なにもしない時の減速.
const float Car::defaultDecel = 0.01f;
// 障害物にぶつかったときの減速率.
const float Car:: colideDecel = 0.08f;
// グリップの減速.
const float Car::gripDecel = 0.2f;
/// <summary>
/// 初期化
/// </summary>
/// <param name="param"></param>
Car::Car(ObjectInit::InitObjKind kind)
	:Actor(kind)
{
	InitSpeedParamater(kind);
	tag = ObjectTag::player;
	ReflectsVelocity();
	wheels = new Wheels(WheelArgumentCarInfo{MGetIdent(),direction,VSize(velocity)});
}


Car::~Car()
{
	SAFE_DELETE(wheels);
}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
{
	conflictVec = conflictInfo.bounceVec;
	conflictVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;
	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	ReflectsVelocity();
}


/// <summary>
/// 進む方向と速さを更新する
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <param name="accelVec">次の更新までに進む方向と速さ</param>
void Car::UpdateVelocity()
{
	const VECTOR accelVec = GetAccelVec();//速度を取ってくる
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	theta *= speedParamator.gripPower - (accelPower - speedParamator.lowestSpeed) / speedParamator.maxSpeed * speedParamator.gripPower;
	velocity = VTransform(accelVec, MGetRotY(theta));
	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::ReflectsVelocity()
{
	//更新する前のポジションを保存
	prevPos = position;
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) > 0.1f)
	{
		direction = VNorm(velocity);
	}
	//ぶつかった時の衝撃影響タイマーがNewされているなら
	if (bounceTimer != nullptr)
	{
		//ぶつかった時の衝撃で移動
		velocity = VScale(conflictVec, static_cast<float>(bounceTimer->GetRemainingTime() / bounceTimer->GetLimitTime()));
		position = VAdd(position, velocity);
	}
	else //衝撃が無くなったら運転できる
	{
		// ポジションを更新.
		position = VAdd(position, velocity);
	}
}
/// <summary>
/// このフレームの間に進む量を出す
/// </summary>
/// <returns>進む量</returns>
VECTOR Car::GetAccelVec()
{
	//ジョイパッドだったらブレーキの対応ボタンを変更
	InputState breakInput = UserInput::GetInputState(Down);
	if (UserInput::IsInputPad())
	{
		breakInput = UserInput::GetInputState(Space);
	}
	//ブレーキした
	if (breakInput == InputState::Hold)
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
	return VScale(direction, accelPower);
}
/// <summary>
/// 移動速度などの初期化
/// </summary>
/// <param name="kind"></param>
void Car::InitSpeedParamater(ObjectInit::InitObjKind kind)
{
	//速さ関連の情報を所得
	auto loader = new CSVFileLoader(InitActor::GetAddDataPass(kind));
	auto strVec = loader->GetLoadStringData();
	speedParamator.acceleSpeed = atof(strVec[acceleSpeed].c_str());
	speedParamator.lowestSpeed = atof(strVec[lowestSpeed].c_str());
	speedParamator.maxSpeed = atof(strVec[maxSpeed].c_str());
	speedParamator.turboAddSpeed = atof(strVec[turboSpeed].c_str());
	speedParamator.turboTime = atof(strVec[turboTime].c_str());
	speedParamator.gripPower = atof(strVec[gripPower].c_str());
	speedParamator.breakPower = atof(strVec[breakePower].c_str());
	speedParamator.turboChargeTime = atof(strVec[turboChargeTime].c_str());
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
