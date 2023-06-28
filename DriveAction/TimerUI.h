#pragma once
#include <string>
#include "UIManager.h"

class Timer;
class NumUI;
/// <summary>
/// 残り時間を描画する
/// </summary>
class TimerUI
{
public:
    TimerUI(Timer* setTimer);
    ~TimerUI();
    //残り時間を描画する
    void Draw();
private:
    //数字のフォント画像
    UIData frameData;
    //小数点
    UIData pointData;
    //小数点の画像
    int pointGraphHandle;
    //フォント画像のサイズ
    int timerFontLoadSize;
    //残り時間を所得する用
    Timer* timer = nullptr;
    //数字を描画する
    NumUI* numUI = nullptr;
};

