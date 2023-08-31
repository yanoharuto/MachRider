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
    /// <summary>
    /// 残り時間のセットと数字画像の読み込み
    /// </summary>
    /// <param name="setTimer">残り時間タイマー</param>
    TimerUI(Timer* setTimer);
    /// <summary>
    /// 特になし
    /// </summary>
    ~TimerUI();
    //残り時間を描画する
    void Draw();
private:
    //数字のフォント画像
    UIData frameUI;
    //小数点
    UIData pointUI;
    //タイマーの枠の横位置
    int frameX;
    //残り時間を所得する用
    Timer* timer = nullptr;
    //数字を描画する
    NumUI* numUI = nullptr;
};

