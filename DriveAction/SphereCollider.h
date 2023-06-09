#pragma once
#include "conflictProccesor.h"
/// <summary>
/// 球体当たり判定
/// </summary>
class SphereCollider final:
    public ConflictProccesor
{
public:
    SphereCollider(Actor* obj);
    /// <summary>
    /// 吹っ飛ぶ方向とかを返す
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};

