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
    Timer(float limitTime);
    ~Timer();
    ///<summary>
    ///���Ԃ����Z�b�g
    ///</summary>
    void Init();
    /// <summary>
    /// �ݒ莞�Ԃ��߂�����
    /// </summary>
    /// <returns>�߂�����True</returns>
    bool IsOverLimitTime();
    /// <summary>
    /// �v������
    /// </summary>
    /// <returns></returns>
    float GetLimitTime();
private:
    //��������
    float limitTime = 0;
    //�v���J�n����
    double startTime = 0;
};

