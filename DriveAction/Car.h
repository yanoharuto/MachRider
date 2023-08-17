#pragma once
#include "Actor.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "Wheels.h"

struct ConflictExamineResultInfo;
struct HitCheckExamineObjectInfo;
class Timer;
class Wheels;

/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car abstract :public Actor
{
public:
	/// <summary>
	/// 車
	/// </summary>
	/// <param name="kind"> 欲しいオブジェクトの種類</param>
	Car(ObjectInit::InitObjKind kind);
	
    virtual ~Car();

	/// <summary>
	/// 移動する前のポジションを渡す
	/// </summary>
	/// <returns></returns>
	virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo() override;

protected:
	/// <summary>
	/// 車がぶつかった時の関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	virtual void ConflictReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// 進む方向と速さを更新する
	/// </summary>
	/// <param name"deltaTime">経過時間</param>
	/// <param name="accelVec">次の更新までに進む方向と速さ</param>
	void UpdateVelocity();
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void ReflectsVelocity() override;

	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <returns>進む量</returns>
	virtual VECTOR GetAccelVec();
	/// <summary>
	/// 移動速度などの初期化
	/// </summary>
	/// <param name="kind"></param>
	void InitSpeedParamater(ObjectInit::InitObjKind kind);
	//スピードのパラメータ
	struct SpeedParamator
	{
		//加速量
		float acceleSpeed;
		//最低速度
		float lowestSpeed;
		//最高速度
		float maxSpeed;
		//急加速速度
		float turboAddSpeed;
		//急加速時間
		float turboTime;
		//曲がる力
		float gripPower;
		//止まる力
		float breakPower;
		//急加速に必要な時間
		float turboChargeTime;
	};
	//車の初期化の種類
	enum CarInitKind
	{
		//加速量
		acceleSpeed = 2,
		//最低速度
		lowestSpeed = 5,
		//最高速度
		maxSpeed = 8,
		//急加速速度
		turboSpeed = 11,
		//急加速時間
		turboTime = 14,
		//曲がる力
		gripPower = 17,
		//止まる力
		breakePower = 20,
		//急加速に必要な時間
		turboChargeTime = 23
	};
	//車のパラメーター
	SpeedParamator speedParamator;
	//速さ
	float accelPower = 0;
	//最初のY座標
	float firstPosY = 0;
	// なにもしない時の減速.
	static const float defaultDecel;
	// グリップの減速.
	static const float gripDecel;
	// 障害物にぶつかったときの減速率.
	static const float colideDecel;
	//衝突して吹っ飛ぶ時間を計る
	Timer* bounceTimer = nullptr;
	//タイヤ
	Wheels* wheels;
	//ぶつかった物体との方向
	VECTOR conflictVec = {};
	//ひとつ前のポジション
	VECTOR prevPos = {};
};