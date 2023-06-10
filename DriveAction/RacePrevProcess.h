#pragma once

#include <string>

#include "UIManager.h"
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
    //�X�V
    void Update();
    //�`��
    void Draw();
    //�I��������
    bool IsProccesEnd();
private:
    //���W���̃A�C�R��
    UIData collectIconData;
    //���������UI
    UIData manualData;
    //�Q�[���̖ڕW
    UIData gamePuroseData;
    //�R�}����p�^�C�}�[
    Timer* frameByFrameTimer;
    //�J�E���g�_�E���p�̃^�C�}�[
    Timer* countDownTimer;
    //�Q�[�����n�߂�O�̃J�E���g�_�E��
    CountDown* countDown;
    //�����I��������
    bool proccesEnd = false;
    //���݂̃R�}
    int iconIncrement = 0;
};