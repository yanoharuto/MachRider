#include "DamageObject.h"
#include "ObjectObserver.h"
DamageObject::DamageObject(ObjectInit::InitObjKind kind, ObjectObserver* setObserver)
    :Actor(kind)
{
    observer = setObserver;
}

DamageObject::~DamageObject()
{
}