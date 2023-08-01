#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// 描画方法を変更するなら第二引数に渡してください
/// </summary>
/// <param name="kind"></param>
/// <param name="setViewer"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = sleep;
}

/// <summary>
/// 当たり判定で当たってたら渡す情報
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}