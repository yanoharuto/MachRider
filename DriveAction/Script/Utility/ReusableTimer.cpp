#include "ReusableTimer.h"
#include "Clock.h"
/// <summary>
/// 計測開始
/// </summary>
/// <param name="setLimitTime">計測する時間</param>
ReusableTimer::ReusableTimer(double setLimitTime)
    :Timer(setLimitTime)
{
 
}
/// <summary>
/// 再利用
/// </summary>
void ReusableTimer::Reuse()
{
    startTime = Clock::GetNowGameTime();
}
