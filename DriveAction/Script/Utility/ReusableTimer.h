#pragma once
#include "Timer.h"
/// <summary>
/// ������x���Ԃ��v���ł���^�C�}�[
/// </summary>
class ReusableTimer : public Timer
{
public:
    /// <summary>
    /// �v���J�n
    /// </summary>
    /// <param name="setLimitTime">�v�����鎞��</param>
    ReusableTimer(double setLimitTime);
    ///<summary>
    /// ������x�v���J�n
    ///</summary>
    void Reuse();
};