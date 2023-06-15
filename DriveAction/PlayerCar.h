#pragma once
#include "Car.h"
class SphereCollider;
class Wheels;
 /// <summary>
 /// プレイヤー(車)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	PlayerCar(VECTOR firstPos,VECTOR direction);
	///デストラクタ
    ~PlayerCar();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update() override;
	void GameReserve() override;
	void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;
private:
	/// <summary>
	/// 車を回転させる
	/// </summary>
	void ModelSetMatrix() const override;
	/// <summary>
	/// 入力すると機体が傾く
	/// </summary>
	void SetInputDir();
	/// <summary>
	/// 走っているときのエフェクトを更新
	/// </summary>
	void EffectUpdate();
	/// <summary>
	/// ダメージを受けた時のリアクション
	/// </summary>
	/// <param name="conflictInfo"></param>
	void DamageReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// ぶつかった時のリアクション
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ConflictReaction(const ConflictExamineResultInfo conflictInfo);

	void DamagePostProccess();
	//高さ
	const float setFirstPosY = 6.0f;
	//走っているときに出るエフェクト
	int runEffect = -1;
	//ぶつかった時に出てくるエフェクト
	int stageConflictEffect = -1;
	//ダメージを受けた時のエフェクト
	int damageEffect = -1;
	//曲がったりするときに傾く速度
	const float twistZRotaSpeed = 1.7f * RAGE;
	//最大傾き度
	const float twistZMaxRota = 27.0f * RAGE;

	
	float upDownSpeed = 2.05f;
	float cosSeed = 0.01f;
	float totalCosSeed;
	//縦に回転する
	float twistZRota = 0.0f;
	//ダメージ
	bool isDamage = false;
	//ダメージを受けた時の操作不可能時間の合計
	const float setDamageReactionTime = 0.5f;
	//ダメージを受けた時に回転する速度
	const float damageReactionRotaSpeed = 75.0f;
	Timer* damageTimer;
};