#pragma once

/// <summary>
/// ���߂�ꂽ���Ԑi�񂾂肷��
/// </summary>
class Timer
{
public:
    /// <summary>
    /// �������ԂƂ����v������
    /// </summary>
    /// <param name="setLimitTime"></param>
    Timer(double limitTime);
    ~Timer();
    ///<summary>
    ///���Ԃ����Z�b�g
    ///</summary>
    void Init();
    /// <summary>
    /// �ݒ莞�Ԃ��߂�����
    /// </summary>
    /// <returns>�߂�����True</returns>
    bool IsOverLimitTime()const;
    /// <summary>
    /// �v������
    /// </summary>
    /// <returns></returns>
    double GetElaspedTime()const;
    /// <summary>
    /// �ŏ��ɐݒ肵���������Ԃ�n��
    /// </summary>
    /// <returns></returns>
    double GetLimitTime()const;
    /// <summary>
    /// �c�莞��
    /// </summary>
    /// <returns></returns>
    double GetRemainingTime()const;
private:
    //��������
    double limitTime = 0;
    //�v���J�n����
    double startTime = 0;
};

