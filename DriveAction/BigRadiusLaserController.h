#pragma once
#include "ActorController.h"

class ObjectSubject;
class ObjectObserver;
class BigRadiusLaserController :
    public ActorController
{
public:
    BigRadiusLaserController(ObjectSubject* sub);
private:
    ObjectObserver* observer;
};

