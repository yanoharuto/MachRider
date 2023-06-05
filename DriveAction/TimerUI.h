#pragma once
#include <string>
#include "UIManager.h"

class Timer;
class NumUI;
class TimerUI
{
public:
    TimerUI(Timer* setTimer);
    ~TimerUI();

    void Draw();
private:
    //数字のフォント画像
    UIData frameData;
    UIData pointData;

    //小数点の画像
    int pointGraphHandle;

    //フォント画像のサイズ
    int timerFontLoadSize;

    Timer* timer = nullptr;
    NumUI* numUI = nullptr;
};

