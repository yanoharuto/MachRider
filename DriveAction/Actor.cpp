#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// �`����@��ύX����Ȃ�������ɓn���Ă�������
/// </summary>
/// <param name="kind"></param>
/// <param name="setViewer"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = sleep;
}

/// <summary>
/// �����蔻��œ������Ă���n�����
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}