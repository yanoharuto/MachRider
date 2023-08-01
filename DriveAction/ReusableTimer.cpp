#include "ReusableTimer.h"
#include "Clock.h"
ReusableTimer::ReusableTimer(double limitTime)
    :Timer(limitTime)
{
}
/// <summary>
/// �ė��p
/// </summary>
void ReusableTimer::Reuse()
{
    startTime = Clock::GetNowGameTime();
}
/// <summary>
/// �������Ԃ��ăZ�b�g
/// </summary>
/// <param name="setLimitTime"></param>
void ReusableTimer::ResetLimitTime(double setLimitTime)
{
    limitTime = setLimitTime;
}
/// <summary>
/// �^�C�}�[��~
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
/// �c�莞��
/// </summary>
/// <returns></returns>
double ReusableTimer::GetElaspedTime()const
{
    //��~��Ȃ�c�莞�Ԃ͒�~�����Ƃ��̎���
    if (stopFlag) return stopTime;

    double nowTime = Clock::GetNowGameTime();
    double elaspedTime = nowTime - startTime;
    return elaspedTime;
}
