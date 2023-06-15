#pragma once
#include "ActorController.h"
class ObjectSubject;
class ObjectObserver;
class BomberController :
    public ActorController
{
public:
    BomberController(ObjectSubject* sub);
private:
    ObjectObserver* observer;
};

