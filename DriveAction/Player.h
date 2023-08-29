#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class SphereCollider;
class PlayerObserver;
class SoundListener;
class PlayerDrawModel;
class PlayerCar;
/// <summary>
/// プレイヤーの車の管理
/// </summary>
class Player final:
    public ActorController
{
public:
    /// <summary>
    /// プレイヤーの車の管理
    /// </summary>
    Player();
    /// <summary>
    /// 車とLisnerのDelete
    /// </summary>
    ~Player();
    /// <summary>
    /// 車の位置とかを渡す
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<PlayerObserver> CreatePlayerObserver() const;
    /// <summary>
    /// 音を聞くために場所を更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() const override;
    /// <summary>
    /// プレイヤーはゲーム終了まで動く
    /// </summary>
    /// <returns></returns>
    bool IsAlive()const override { return true; };
private:
    //プレイヤーの車の当たり判定
    SphereCollider* collider;
    //操作する車
    PlayerCar* car;
    //描画に使う
    PlayerDrawModel* playerDrawer;
    //音を聞く場所の更新
    SoundListener* listener = nullptr;
    //ダメージを受けるクールタイム
    const float setDamageCoolTime = 0.1f;
    std::shared_ptr<PlayerObserver> playerObserver;
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