#pragma once
#include <iostream>
#include<memory>
#include "DxLib.h"
#include "ActorController.h"
class SphereCollider;
class ObjectSubject;
class ObjectObserver;
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
    /// <summary>
    /// 車の位置とかを渡す
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<ObjectObserver> CreatePlayerObserver() const;
    void GameReserve()override;
private:
    SphereCollider* collider;
    ObjectSubject* subject;
    std::shared_ptr <ObjectObserver> observer;
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