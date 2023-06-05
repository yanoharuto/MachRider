#pragma once
#include "CPUCar.h"
class Enemy :
    public CPUCar
{
public:

    Enemy(CarInfomation carParam, int duplicateModelHandle);
    ~Enemy();
    virtual void Update(const  VECTOR playerPos, ItemInfo itemInfo);
    virtual void Draw();
private:
    const float scale = 8.0f;
    
};

