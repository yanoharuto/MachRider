#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// 制限時間とかを計測する
/// </summary>
/// <param name="setLimitTime"></param>
Timer::Timer(double setLimitTime)
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
bool Timer::IsOverLimitTime()const
{
    return  limitTime - GetElaspedTime() < 0;
}
/// <summary>
/// 経過時間
/// </summary>
/// <returns></returns>
double Timer::GetElaspedTime()const
{    
    double nowTime = Clock::GetNowGameTime();
    double elaspedTime = nowTime - startTime;
    return elaspedTime;
}
/// <summary>
/// タイマーに設定された時間
/// </summary>
/// <returns></returns>
double Timer::GetLimitTime() const
{
    return limitTime;
}
/// <summary>
/// 残り時間を所得
/// </summary>
/// <returns></returns>
double Timer::GetRemainingTime() const
{
    return limitTime - GetElaspedTime();
}
