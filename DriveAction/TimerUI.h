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
    //�����̃t�H���g�摜
    UIData frameData;
    UIData pointData;

    //�����_�̉摜
    int pointGraphHandle;

    //�t�H���g�摜�̃T�C�Y
    int timerFontLoadSize;

    Timer* timer = nullptr;
    NumUI* numUI = nullptr;
};

