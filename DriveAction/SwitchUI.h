#pragma once
#include "DxLib.h"
class Timer;
class SwitchUI
{
public:
    SwitchUI();
    ~SwitchUI();
    void Update();
    void Draw();
private:
    Timer* timer;
    const float span = 2.0f;
};

