#include "ReusableTimer.h"
#include "Clock.h"
ReusableTimer::ReusableTimer(double limitTime)
    :Timer(limitTime)
{
}
/// <summary>
/// 再利用
/// </summary>
void ReusableTimer::Reuse()
{
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// 制限時間を再セット
/// </summary>
/// <param name="setLimitTime"></param>
void ReusableTimer::ResetLimitTime(double setLimitTime)
{
    limitTime = setLimitTime;
}
/// <summary>
/// タイマー停止
/// </summary>
void ReusableTimer::Stop()
{
    if (!stopFlag)
    {
        stopTime = GetElaspedTime();
        stopFlag = true;
    }
}
/// <summary>
/// 残り時間
/// </summary>
/// <returns></returns>
double ReusableTimer::GetElaspedTime()const
{
    //停止後なら残り時間は停止したときの時間
    if (stopFlag) return stopTime;

    double nowTime = Clock::GetNowGameTime();
    double elaspedTime = nowTime - startTime;
    return elaspedTime;
}
