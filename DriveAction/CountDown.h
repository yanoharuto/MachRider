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
    bool IsCountDownEnd();
    void DrawUI();
private:
    bool countDownEnd;
    bool countStart = false;
    UIData countDownUIData;
    const std::string countDownSE = "countdown.mp3";
    int uiNum = -1;
    Timer* timer;
};

