#pragma once
#include <iostream>
#include<memory>
#include "DxLib.h"
#include "ActorController.h"
class SphereCollider;
class ObjectObserver;
class SoundListener;
/// <summary>
/// プレイヤーの車やアイテムの処理を呼び出す
/// </summary>
class Player final:
    public ActorController
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos,VECTOR direction);
    ~Player();
    /// <summary>
    /// 車の位置とかを渡す
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<ObjectObserver> CreatePlayerObserver() const;
    /// <summary>
    /// 音を聞くために場所を更新
    /// </summary>
    void Update()override;
private:
    //プレイヤーの車の当たり判定
    SphereCollider* collider;
    //プレイヤーの位置などを教える
    std::shared_ptr<ObjectObserver> observer;

    //音を聞く場所の更新
    SoundListener* listener = nullptr;
    //ダメージを受けるクールタイム
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