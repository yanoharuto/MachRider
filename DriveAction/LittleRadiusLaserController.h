#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
class ObjectSubject;
class ObjectObserver;
/// <summary>
/// 小さく回るレーザー
/// </summary>
class LittleRadiusLaserController :
    public ActorController
{
public:
    LittleRadiusLaserController(ObjectSubject* sub);
private:
    ObjectObserver* observer;
};