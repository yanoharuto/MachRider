#pragma once
#include "Actor.h"

#include "InitObjKind.h"

class ObjectObserver;
class DamageObject abstract:
    public Actor
{
public:
    DamageObject(ObjectInit::InitObjKind kind,ObjectObserver* setObserver);

    virtual ~DamageObject();
protected:
    ObjectObserver* observer;
};

