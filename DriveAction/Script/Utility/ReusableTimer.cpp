#include "ReusableTimer.h"
#include "Clock.h"
/// <summary>
/// �v���J�n
/// </summary>
/// <param name="setLimitTime">�v�����鎞��</param>
ReusableTimer::ReusableTimer(double setLimitTime)
    :Timer(setLimitTime)
{
 
}
/// <summary>
/// �ė��p
/// </summary>
void ReusableTimer::Reuse()
{
    startTime = Clock::GetNowGameTime();
}
