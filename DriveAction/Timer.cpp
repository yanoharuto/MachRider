#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
#include "Clock.h"
/// <summary>
/// �������ԂƂ����v������
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
bool Timer::IsOverLimitTime()const
{
    return  limitTime - GetElaspedTime() < 0;
}
/// <summary>
/// �o�ߎ���
/// </summary>
/// <returns></returns>
double Timer::GetElaspedTime()const
{    
    double nowTime = Clock::GetNowGameTime();
    double elaspedTime = nowTime - startTime;
    return elaspedTime;
}
/// <summary>
/// �^�C�}�[�ɐݒ肳�ꂽ����
/// </summary>
/// <returns></returns>
double Timer::GetLimitTime() const
{
    return limitTime;
}
/// <summary>
/// �c�莞�Ԃ�����
/// </summary>
/// <returns></returns>
double Timer::GetRemainingTime() const
{
    return limitTime - GetElaspedTime();
}
