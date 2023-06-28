#pragma once
#include <iostream>
#include <memory>
class Timer;
class ActorControllerManager;
class DemoCarController;
class TitleCamera;
class ObjectObserver;
class ShadowMap;
class TitleDemo
{
public:
    TitleDemo();
    ~TitleDemo();
    void Update();
    void Draw()const;
private:
    ActorControllerManager* manager;
    DemoCarController* demoCarController;
    TitleCamera* camera;
    Timer* initTimer;
    ShadowMap* shadowMap;
    std::shared_ptr<ObjectObserver> demoObserver;
    const float initTime = 15.0f;
    const float fadeSpeed = 3;
    bool isAValueIncrement = true;
    float fadeValue;
};