#pragma once
#include <string>
#include "UIManager.h"
class Timer;
class NumUI;
/// <summary>
/// �c�莞�Ԃ�`�悷��
/// </summary>
class TimerUI
{
public:
    /// <summary>
    /// �c�莞�Ԃ̃Z�b�g�Ɛ����摜�̓ǂݍ���
    /// </summary>
    /// <param name="setTimer">�c�莞�ԃ^�C�}�[</param>
    TimerUI(Timer* setTimer);
    /// <summary>
    /// ���ɂȂ�
    /// </summary>
    ~TimerUI();
    //�c�莞�Ԃ�`�悷��
    void Draw();
private:
    //�����̃t�H���g�摜
    UIData frameUI;
    //�����_
    UIData pointUI;
    //�^�C�}�[�̘g�̉��ʒu
    int frameX;
    //�c�莞�Ԃ���������p
    Timer* timer = nullptr;
    //������`�悷��
    NumUI* numUI = nullptr;
};

