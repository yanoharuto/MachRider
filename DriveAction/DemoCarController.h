#pragma once
#include <iostream>
#include <memory>
#include "ActorController.h"
#include "DxLib.h"
class DemoCar;
class Timer;
class ObjectSubject;
class ObjectObserver;
class DemoCarController :
    public ActorController
{
public:
    DemoCarController(VECTOR setPos,VECTOR setDir);
    ~DemoCarController()override;
    void Update()override;
    bool IsAlive()const override;
    void Draw()const override;
    void InitPosition();
    std::shared_ptr<ObjectObserver> CreateCarObserver();
private:
    DemoCar* demoCar;
    ObjectSubject* subject;
};