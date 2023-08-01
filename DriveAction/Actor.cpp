#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// •`‰æ•û–@‚ğ•ÏX‚·‚é‚È‚ç‘æ“ñˆø”‚É“n‚µ‚Ä‚­‚¾‚³‚¢
/// </summary>
/// <param name="kind"></param>
/// <param name="setViewer"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = sleep;
}

/// <summary>
/// “–‚½‚è”»’è‚Å“–‚½‚Á‚Ä‚½‚ç“n‚·î•ñ
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}