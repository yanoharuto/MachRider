#pragma once
#include "Timer.h"
/// <summary>
/// ������x���Ԃ��v���ł���^�C�}�[
/// </summary>
class ReusableTimer :
    public Timer
{
public:
    /// <summary>
    /// �ė��p�\�^�C�}�[
    /// </summary>
    /// <param name="limitTime"></param>
    ReusableTimer(double limitTime);

    ///<summary>
    /// ������x�v���J�n
    ///</summary>
    void Reuse();
    /// <summary>
    /// �������Ԃ��ăZ�b�g
    /// </summary>
    /// <param name="limitTime"></param>
    void ResetLimitTime(double setLimitTime);
    /// <summary>
    /// �^�C�}�[��~
    /// </summary>
    void Stop();
    /// <summary>
    /// �c�莞��
    /// </summary>
    /// <returns></returns>
    double GetElaspedTime() const override;
private:
    //��~����
    bool stopFlag = false;
    //��~�����Ƃ��̎c�莞��
    double stopTime;
};
