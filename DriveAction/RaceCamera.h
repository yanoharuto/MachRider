#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;
/// <summary>
/// �V��ł���Ƃ��̃J����
/// </summary>
class RaceCamera final : Camera
{
public:
    RaceCamera(std::weak_ptr<ObjectObserver> player);
    void Update();
};

