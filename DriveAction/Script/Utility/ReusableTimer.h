#pragma once
#include "Timer.h"
/// <summary>
/// もう一度時間を計測できるタイマー
/// </summary>
class ReusableTimer : public Timer
{
public:
    /// <summary>
    /// 計測開始
    /// </summary>
    /// <param name="setLimitTime">計測する時間</param>
    ReusableTimer(double setLimitTime);
    ///<summary>
    /// もう一度計測開始
    ///</summary>
    void Reuse();
};