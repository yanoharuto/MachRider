#include "ReusableTimer.h"
#include "Clock.h"
ReusableTimer::ReusableTimer(double limitTime)
    :Timer(limitTime)
{
}
/// <summary>
/// Ä—˜—p
/// </summary>
void ReusableTimer::Reuse()
{
    startTime = Clock::GetNowGameTime();
}

void ReusableTimer::ResetLimitTime(double setLimitTime)
{
    limitTime = setLimitTime;
}
