#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// 球体当たり判定
/// </summary>
class SphereCollider final:
    public SphereHitChecker
{
public:
    /// <summary>
/// 球体当たり判定
/// </summary>
    SphereCollider(Actor* obj);
    /// <summary>
    /// 吹っ飛ぶ方向とかを返す
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo)override;
};