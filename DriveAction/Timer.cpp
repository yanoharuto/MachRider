#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// �������ԂƂ����v������
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
/// ���Ԃ����Z�b�g
/// </summary>
void Timer::Init()
{
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// �ݒ莞�Ԃ��߂�����
/// </summary>
/// <returns>�߂�����True</returns>
bool Timer::IsOverLimitTime()
{
    return  Clock::GetNowGameTime() - startTime > limitTime;
}
/// <summary>
/// �v������
/// </summary>
/// <returns></returns>
float Timer::GetLimitTime()
{
    return limitTime - (Clock::GetNowGameTime() - startTime);
}
