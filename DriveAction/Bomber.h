#pragma once
#include "DamageObject.h"
class SphereCollider;
class ConflictProcessor;
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
class Bomber final :public DamageObject
{
public:
    /// <summary>
/// 上から下に落とす爆弾
/// </summary>
    Bomber(std::unique_ptr<ObjectObserver> setObserver);
    /// <summary>
    /// 球当たり判定削除
    /// </summary>
    ~Bomber() override;
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
    /// <summary>
    /// 当たり判定削除
    /// </summary>
    void EraceCollider();
    //最初の落下速度
    static const float setFallingSpeed;
    //落下速度
    float fallingSpeed = setFallingSpeed;
    //重力
    static const float gravityPower;
    //燃えているときのエフェクト
    int burnEffect = -1;
    //当たり判定
    SphereCollider* collider = nullptr;
    //衝突処理実行役
    ConflictProcessor* conflictProcessor;
};