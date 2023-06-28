#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;
/// <summary>
/// —V‚ñ‚Å‚¢‚é‚Æ‚«‚ÌƒJƒƒ‰
/// </summary>
class RaceCamera final : Camera
{
public:
    RaceCamera(std::weak_ptr<ObjectObserver> player);
    void Update();
};

