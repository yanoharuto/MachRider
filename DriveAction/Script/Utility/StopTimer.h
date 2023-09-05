#pragma once
#include "Timer.h"
/// <summary>
/// �~�߂邱�Ƃ��o����^�C�}�[
/// </summary>
class StopTimer : public Timer
{
public:
    /// <summary>
    /// �v���J�n
    /// </summary>
    /// <param name="setLimitTime">�v������</param>
    StopTimer(double setLimitTime);
    /// <summary>
    /// �^�C�}�[��~
    /// </summary>
    void Stop();
    /// <summary>
    /// �o�ߎ���
    /// </summary>
    /// <returns>���b�o������</returns>
    double GetElaspedTime()const override;
private:
    //��~����
    bool stopFlag = false;
    //��~�����Ƃ��̎c�莞��
    double stopTime;
};