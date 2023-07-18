#pragma once
#include "Car.h"
#include "EffectManager.h"
#include "UserInput.h"
class SphereCollider;

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
    ~PlayerCar()override;
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update() override;
	/// <summary>
	/// ゲームが始まる前の演出とか
	/// </summary>
	void GameReserve() override;
	/// <summary>
	/// ぶつかった時の処理
	/// </summary>
	/// <param name="conflictInfo"></param>
	void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;

private:
	/// <summary>
	/// 加速用ベクトルを作る
	/// </summary>
	/// <returns></returns>
	VECTOR GetAccelVec()override;
	/// <summary>
	/// 車を回転させる
	/// </summary>
	void ModelSetMatrix() const override;
	/// <summary>
	/// 入力するとTwistZRotaが変更する
	/// </summary>
	void SetTwistZRota();
	/// <summary>
	/// 走っているときのエフェクトを更新
	/// </summary>
	void UpdateEffects();
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
	/// <summary>
	/// ダメージを受けた後の処理。無敵時間復帰など
	/// </summary>
	void DamagePostProccess();
	/// <summary>
	/// 左右に押しながら下を離すとブースト
	/// </summary>
	/// <returns></returns>
	float GetTurboPower();
	/// <summary>
	/// エフェクトの位置と方向をセット
	/// </summary>
	/// <param name="playEffect"></param>
	/// <param name="pos"></param>
	/// <param name="dir"></param>
	/// <param name="effectKind"></param>
	void UpdateEffect(int* playEffect,VECTOR pos,VECTOR dir,EffectKind effectKind);
	/// <summary>
	/// エフェクトを消去
	/// </summary>
	/// <param name="effectHandle">消したいエフェクト</param>
	void DeleteEffect(int effectHandle);
	//高さ
	const float setFirstPosY = 6.0f;
	//走っているときに出るエフェクト
	int windEffect = -1;
	//ぶつかった時のエフェクト
	int clashEffect = -1;
	//急加速中
	bool isTurbo = false;
	//急加速準備中
	bool isTurboReserve = false;
	//衝突している最中か調べる
	bool isConflictFlag = false;
	//連続衝突
	bool isSerialConflict = false;
	//加速チャージタイム
	float turboChargeTime = 0;
	//ダメージを受けた時のエフェクト
	int damageEffect = -1;
	//ターボ準備中に出るエフェクト
	int turboCourceEffect = -1;
	//通常時の後ろの炎
	int defaultBurnerEffect = -1;
	//チャージ中の後ろの炎
	int chargeBurnerEffect = -1;
	//加速中の後ろの炎
	int turboBurnerEffect = -1;
	//曲がったりするときに傾く速度
	const float twistZRotaSpeed = 1.7f * RAGE;
	//最大傾き度
	const float twistZMaxRota = 27.0f * RAGE;
	//上下に移動する速度
	float upDownSpeed = 2.05f;
	//totalCosSeedを増加させ続ける量
	float cosSeed = 0.01f;
	//upDownSpeedとcosSeedによって変動する
	float totalCosSeed = 0;
	//縦に回転する
	float twistZRota = 0.0f;
	//ダメージ
	bool isDamage = false;
	//ダメージを受けた時の操作不可能時間の合計
	const float setDamageReactionTime = 1.0f;
	//ダメージを受けた時に回転する速度
	const float damageReactionRotaSpeed = 15.0f;
	//無敵時間のタイマー
	Timer* damageTimer = nullptr;
	//ターボ時間
	Timer* turboTimer = nullptr;
};