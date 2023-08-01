#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"


/// <summary>
/// 動くやつ
/// </summary>
class Actor abstract:
    public Object
{
public:
    Actor(ObjectInit::InitObjKind kind);
    

    virtual ~Actor()
    {
    };

    /// <summary>
    /// 衝突処理
    /// </summary>
    virtual void ConflictProcess(const ConflictExamineResultInfo conflictInfo) {};

    /// <summary>
    /// 当たり判定で当たってたら渡す情報
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo();
    /// <summary>
    /// ゲームが始まる前にすること
    /// </summary>
    virtual void GameReserve() {};
protected:
};