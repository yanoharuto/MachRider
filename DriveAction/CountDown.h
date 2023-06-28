#pragma once
#include <string>
#include "DxLib.h"
#include "Timer.h"
#include "UIManager.h"
class CountDown
{
public:
    CountDown(Timer* timer);
    ~CountDown();
    void Update();
    bool IsCountDownEnd()const;
    bool IsPlayCountDownSound()const;
    virtual void DrawUI()const;
protected:
    bool countDownEnd = false;
    bool countStart = false;
    UIData countDownUIData;
    UIData endUI;
    int uiNum = -1;
    Timer* timer;
};

