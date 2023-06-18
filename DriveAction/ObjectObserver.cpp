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

bool ObjectObserver::GetSubjectState(Object::ObjectState compareState) const
{
    return subject->GetObjectState(compareState);
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
