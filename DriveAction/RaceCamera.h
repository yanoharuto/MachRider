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
    RaceCamera(std::shared_ptr<ObjectObserver> player);
    ~RaceCamera() override;
    void Update();
private:
    //プレイヤーの位置を教えてくれるやつ
    std::weak_ptr<ObjectObserver> playerObserver;
};

