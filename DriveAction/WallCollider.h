#pragma once
#include "ConflictProccesor.h"
/// <summary>
/// ステージの外に出ないようにする壁
/// </summary>
class WallCollider :
    public ConflictProccesor
{
public:
    /// <summary>
    /// ステージの外に出ないようにする壁
    /// </summary>
    /// <param name="owner"></param>
    /// <param name="setFirstPos">これ以上の値になったら跳ね返す</param>
    /// <param name="setEndPos">これ以下の値になったら跳ね返す</param>
    WallCollider(Actor* owner,VECTOR setFirstPos,VECTOR setEndPos);
    ~WallCollider();
    /// <summary>
    /// 当たったか調べる
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) override;
private:
    //これ以上の値になったら跳ね返す
    VECTOR firstPos;
    //これ以下の値になったら跳ね返す
    VECTOR endPos;
};

