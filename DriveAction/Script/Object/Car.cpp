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
	wheels = new Wheels();
}


Car::~Car()
{
	SAFE_DELETE(wheels);
}

/// <summary>
/// 車がぶつかった時の関数
/// </summary>
/// <param name="conflictInfo">ぶつかった時の結果</param>
void Car::ConflictReaction(CollisionResultInfo conflictInfo)
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
void Car::UpdateVelocity()
{
	//加速する
	UpdateAccelPower();
	//移動量を作成
	VECTOR accelVec = VScale(direction, accelPower);
	//タイヤの向きから進行方向のずれを所得
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	//早いほど曲がりにくくなるようにする
	theta *= speedParamator.gripPower - accelPower / speedParamator.maxSpeed;
	//加速量をタイヤの向きで変化させる
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
void Car::UpdateAccelPower()
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
	speedParamator.acceleSpeed = SAFE_STR_TO_F(strVec[acceleSpeed]);
	speedParamator.lowestSpeed = SAFE_STR_TO_F(strVec[lowestSpeed]);
	speedParamator.maxSpeed = SAFE_STR_TO_F(strVec[maxSpeed]);
	speedParamator.turboAddSpeed = SAFE_STR_TO_F(strVec[turboSpeed]);
	speedParamator.turboTime = SAFE_STR_TO_F(strVec[turboTime]);
	speedParamator.gripPower = SAFE_STR_TO_F(strVec[gripPower]);
	speedParamator.breakPower = SAFE_STR_TO_F(strVec[breakePower]);
	speedParamator.turboChargeTime = SAFE_STR_TO_F(strVec[turboChargeTime]);
}

/// <summary>
/// 移動する前のポジションを渡す
/// </summary>
/// <returns></returns>
HitCheckInfo Car::GetHitCheckExamineInfo()
{
	HitCheckInfo info;
	info.pos = prevPos;
	info.radius = radius;
	info.velocity = velocity;
	return info;
}
