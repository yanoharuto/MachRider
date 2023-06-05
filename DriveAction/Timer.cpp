#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// 制限時間とかを計測する
/// </summary>
/// <param name="setLimitTime"></param>
Timer::Timer(float setLimitTime)
{
    limitTime = setLimitTime;
    startTime = Clock::GetNowGameTime();
}

Timer::~Timer()
{
}
/// <summary>
/// 時間をリセット
/// </summary>
void Timer::Init()
{
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// 設定時間を過ぎたか
/// </summary>
/// <returns>過ぎたらTrue</returns>
bool Timer::IsOverLimitTime()
{
    return  Clock::GetNowGameTime() - startTime > limitTime;
}
/// <summary>
/// 計測時間
/// </summary>
/// <returns></returns>
float Timer::GetLimitTime()
{
    return limitTime - (Clock::GetNowGameTime() - startTime);
}
