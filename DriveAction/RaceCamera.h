#pragma once
#include "Camera.h"
class ObjectObserver;
class ObjectSubject;
class RacerManager;
class RaceCamera final : Camera
{
public:
    RaceCamera(RacerManager* manager);
    ~RaceCamera() override;
    void Update();
private:
    //プレイヤーの位置を教えてくれるやつ
    ObjectObserver* playerObserver;
};

