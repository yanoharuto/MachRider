#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// ��������郌�[�U�[
/// </summary>
class LittleRadiusLaserController :
    public ActorController
{
public:
    LittleRadiusLaserController(ObjectSubject* sub);
private:
    ObjectObserver* observer;
};