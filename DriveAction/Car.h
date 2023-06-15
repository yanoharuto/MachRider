#pragma once
#include "Actor.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "Wheels.h"


struct ConflictExamineResultInfo;
struct HitCheckExamineObjectInfo;
struct ObjInfo;
struct InputInfo;
class Timer;
class Wheels;

/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car abstract :public Actor
{
public:
	/// <summary>
	/// 初期位置や方角とか
	/// </summary>
	/// <param name="firstPos"></param>
	/// <param name="firstDir"></param>
	/// <param name="destinationPos"></param>
	/// <param name="soundPlayer"></param>
	Car(ObjectInit::InitObjKind);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update();
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="conflictInfo">ぶつかったかオブジェクトの情報</param>
	virtual void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;

	/// <summary>
	/// 移動する前のポジションを渡す
	/// </summary>
	/// <returns></returns>
	HitCheckExamineObjectInfo GetHitCheckExamineInfo() override;

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
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void ReflectsVelocity() override;

	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <param name="handleDir">入力された方向</param>
	/// <param name="outsideHitFlag">コースの外にいるか</param>
	/// <param name="deltaTime">経過時間</param>
	/// <param name="soundPlayer">音を出すやつ</param>
	/// <returns>進む量</returns>
	VECTOR GetAccelVec();

	void InitParamater(ObjectInit::InitObjKind kind) override;
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
	};
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
		breakePower = 20
	};
	//車のパラメーター
	SpeedParamator speedParamator;
	//速さ
	float accelPower = 0;
	//最初のY座標
	float firstPosY = 0;
	//加速
	float turboPower;
	// なにもしない時の減速.
	static const float defaultDecel;
	// グリップの減速.
	static const float gripDecel;
	// 障害物にぶつかったときの減速率.
	static const float colideDecel;
	//タイヤ
	Wheels* wheels;
	//ぶつかった物体との方向
	VECTOR collVec = {};
	//ひとつ前のポジション
	VECTOR prevPos = {};
};
