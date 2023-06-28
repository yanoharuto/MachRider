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

Object::ObjectState ObjectObserver::GetSubjectState() const
{
    return subject->GetObjectState();
}

VECTOR ObjectObserver::GetSubjectPos() const
{
    return subject->GetObjPos();
}

VECTOR ObjectObserver::GetSubjectDir() const
{
    return subject->GetObjDir();
}

int ObjectObserver::GetSubjectHitCount(Object::ObjectTag objTag) const
{
    return subject->GetTagObjectHitCount(objTag);
}
