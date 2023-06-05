#include "ObjectObserver.h"
#include "Object.h"
#include "ObjectSubject.h"
ObjectObserver::ObjectObserver(ObjectSubject* setSubject)
{
    subject = setSubject;
}

ObjectObserver::~ObjectObserver()
{
}

VECTOR ObjectObserver::GetSubPos()
{
    return subject->GetObjPos();
}

VECTOR ObjectObserver::GetSubDir()
{
    return subject->GetObjDir();
}

int ObjectObserver::GetObjHitCount(Object::ObjectTag objTag)
{
    return subject->GetTagObjectHitCount(objTag);
}
