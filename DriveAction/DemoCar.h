#pragma once
#include "Car.h"
class DemoCar :
    public Car
{
public:
    DemoCar(VECTOR setPos,VECTOR setDir);
    ~DemoCar()override;

    void InitPosition();

    void Update()override;
private:
    void EffectUpdate();
    VECTOR GetAccelVec()override;
    int runEffect = -1;
    VECTOR firstPos;
    VECTOR firstDir;
};

