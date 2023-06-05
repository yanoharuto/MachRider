#pragma once
#include "Racer.h"
#include "CPUCar.h"

class CPU :
    public Racer
{
public:
    CPU();
    CPU(VECTOR firstPos);
    ~CPU();
    void Update()override;
private:
};

