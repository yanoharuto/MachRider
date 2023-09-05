#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "UIManager.h"
class NumUI;
class Timer;
class CountDown;
class PlayManual;
class ReusableTimer;
class GameManager;
/// <summary>
/// ���[�X�O�̏�������Ă����
/// </summary>
class GamePrevProcess
{
public:
    /// <summary>
    /// ����UI�̏�����
    /// </summary>
    GamePrevProcess();
    /// <summary>
    /// �J�E���g�_�E���Ȃǂ����
    /// </summary>
    ~GamePrevProcess();
    /// <summary>
    /// �J�E���g�_�E���̍X�V
    /// </summary>
    void Update(std::shared_ptr<GameManager> gameObj);
    /// <summary>
    /// �V�ѕ��ƃJ�E���g�_�E���̕`��
    /// </summary>
    void Draw() const;
    /// <summary>
    /// �������I��������
    /// </summary>
    /// <returns></returns>
    bool IsEndProcess();
private:
    //���W���̃A�C�R��
    UIData collectIconData;
    //���������UI
    PlayManual* playManual;
    //�Q�[���̖ڕW
    UIData gamePuroseData;
    //���W�A�C�e���̏W�߂鐔
    NumUI* collectItemNum;
    //�R�}����p�^�C�}�[
    ReusableTimer* frameByFrameTimer;
    //�J�E���g�_�E���p�̃^�C�}�[
    std::shared_ptr<Timer> countDownTimer;
    //�Q�[�����n�߂�O�̃J�E���g�_�E��
    CountDown* countDown;
    //�����I��������
    bool processEnd = false;
    //���W�A�C�e���A�C�R���̃R�}����ԍ�
    int iconGHIndex = 0;
    //�Q�[���̖ڕW���������Ă���Ԃ͎���𔒂�����
    int fadeValue = 0;
    //�X�^�[�g�̃J�E���g�_�E����5�b
    const float startTimerLimit = 5;
};