#pragma once
#include "DamageObject.h"
class SphereCollider;
class ConflictProcessor;
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
class Rocket final :public DamageObject
{
public:
    Rocket(std::unique_ptr<ObjectObserver> setObserver);
    ~Rocket() override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// 衝突後の処理
    /// </summary>
    void ConflictProcess(ConflictExamineResultInfo resultInfo)override;
private:
    //最初の落下速度
    static const float setFallingSpeed;
    //落下速度
    float fallingSpeed = setFallingSpeed;
    //重力
    static const float gravityPower;
    //燃えた時の当たり判定の大きさ
    static const float setBurnRadius;
    //燃えているときのエフェクト
    int burnEffect = -1;
    //地面に触れているか
    bool onGround = false;
    //当たり判定
    SphereCollider* collider = nullptr;
    //衝突処理実行役
    ConflictProcessor* conflictProcessor;
};