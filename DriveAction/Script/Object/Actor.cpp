#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// 描画方法を変更するなら第二引数に渡してください
/// </summary>
/// <param name="kind"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = ObjectState::sleep;
}

/// <summary>
/// 当たり判定で当たってたら渡す情報
/// </summary>
/// <returns></returns>
HitCheckInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
/// <summary>
///　ゲーム開始準備処理。オーバーライドしなければ普通の更新
/// </summary>
void Actor::PrepareGame()
{
    Update();
}
