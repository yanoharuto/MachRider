#pragma once
#include <string>
#include "UIManager.h"

class Timer;
class NumUI;
/// <summary>
/// �c�莞�Ԃ�`�悷��
/// </summary>
class TimerUI
{
public:
    TimerUI(Timer* setTimer);
    ~TimerUI();
    //�c�莞�Ԃ�`�悷��
    void Draw();
private:
    //�����̃t�H���g�摜
    UIData frameData;
    //�����_
    UIData pointData;
    //�����_�̉摜
    int pointGraphHandle;
    //�t�H���g�摜�̃T�C�Y
    int timerFontLoadSize;
    //�c�莞�Ԃ���������p
    Timer* timer = nullptr;
    //������`�悷��
    NumUI* numUI = nullptr;
};

