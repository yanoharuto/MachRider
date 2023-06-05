#pragma once
#include "DxLib.h"
#include "Racer.h"
class SphereCollider;
class ObjectSubject;
class Timer;
/// <summary>
/// プレイヤーの車やアイテムの処理を呼び出す
/// </summary>
class Player final:
    public Racer 
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos);
    ~Player();
    /// <summary>
    /// プレイヤーの更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObjGene"></param>
    void Update()override;
    /// <summary>
    /// 車の位置とかを渡す
    /// </summary>
    /// <returns></returns>
    ObjectSubject* GetSubject();
private:
    SphereCollider* collider;
    ObjectSubject* subject;
    const float setDamageCoolTime = 1.5f;
};

/// <summary>
/// プレイヤーのUI周りに必要な情報
/// </summary>
enum PlayerRelatedInfo
{
    //当たった回数
    damageObjHitCount = 0,
    //コインを回収した回数
    hitCoinCount = 1,
    //速度
    accelPower = 3,
};