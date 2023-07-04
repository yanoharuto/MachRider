#pragma once

#include <string>
#include "UIManager.h"
class NumUI;
class Timer;
class CountDown;
/// <summary>
/// ���[�X�O�̏�������Ă����
/// </summary>
class RacePrevProcess
{
public:
    RacePrevProcess();
    ~RacePrevProcess();
    /// <summary>
    /// �J�E���g�_�E���̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �V�ѕ��ƃJ�E���g�_�E���̕`��
    /// </summary>
    void Draw() const;
    /// <summary>
    /// �������I��������
    /// </summary>
    /// <returns></returns>
    bool IsProccesEnd();
private:
    //���W���̃A�C�R��
    UIData collectIconData;
    //���������UI
    UIData manualData;
    //�Q�[���̖ڕW
    UIData gamePuroseData;
    //���W�A�C�e���̏W�߂鐔
    NumUI* collectItemNum;
    //�R�}����p�^�C�}�[
    Timer* frameByFrameTimer;
    //�J�E���g�_�E���p�̃^�C�}�[
    Timer* countDownTimer;
    //�Q�[�����n�߂�O�̃J�E���g�_�E��
    CountDown* countDown;
    //�����I��������
    bool proccesEnd = false;
    //���W�A�C�e���A�C�R���̃R�}����ԍ�
    int iconGHIndex = 0;
    //�Q�[���̖ڕW���������Ă���Ԃ͎���𔒂�����
    int fadeValue = 0;
    //�X�^�[�g�̃J�E���g�_�E����5�b
    const float startTimerLimit = 5;
};