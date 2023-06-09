#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;
/// <summary>
/// 遊んでいるときのカメラ
/// </summary>
class RaceCamera final : Camera
{
public:
    RaceCamera(std::weak_ptr<ObjectObserver> player);
    void Update();
};

