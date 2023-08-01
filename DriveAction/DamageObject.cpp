#include "DamageObject.h"
#include "ObjectObserver.h"
/// <summary>
/// 発射した奴の位置とかが分かるポインターをください
/// </summary>
/// <param name="kind"></param>
/// <param name="setObserver"></param>
DamageObject::DamageObject(ObjectInit::InitObjKind kind, std::unique_ptr<ObjectObserver> setObserver)
    :Actor(kind)
{
    observer = std::move(setObserver);
    tag = damageObject;
}

DamageObject::~DamageObject()
{
}