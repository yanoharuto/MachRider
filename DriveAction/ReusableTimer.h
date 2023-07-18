#pragma once
#include "Timer.h"
/// <summary>
/// もう一度時間を計測できるタイマー
/// </summary>
class ReusableTimer :
    public Timer
{
public:
    /// <summary>
    /// 再利用可能タイマー
    /// </summary>
    /// <param name="limitTime"></param>
    ReusableTimer(double limitTime);

    ///<summary>
    /// もう一度計測開始
    ///</summary>
    void Reuse();
    /// <summary>
    /// 制限時間を再セット
    /// </summary>
    /// <param name="limitTime"></param>
    void ResetLimitTime(double setLimitTime);
};

