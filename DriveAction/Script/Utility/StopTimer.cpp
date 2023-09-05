#include "StopTimer.h"
#include "Clock.h"
/// <summary>
/// 計測開始
/// </summary>
/// <param name="setLimitTime">計測時間</param>
StopTimer::StopTimer(double setLimitTime)
    :Timer(setLimitTime)
{
    stopFlag = false;
    stopTime = 0;
}
/// <summary>
/// タイマー停止
/// </summary>
void StopTimer::Stop()
{
    if(!stopFlag)
    {
        stopTime = Clock::GetNowGameTime() - startTime;
        stopFlag = true;
    }
}
/// <summary>
/// 経過時間
/// </summary>
/// <returns>何秒経ったか</returns>
double StopTimer::GetElaspedTime()const
{
    //停止後なら残り時間は停止したときの残り時間
    if (stopFlag) 
    {
        return stopTime;
    }
    //残り時間
    double elaspedTime = Clock::GetNowGameTime() - startTime;
    return elaspedTime;
}