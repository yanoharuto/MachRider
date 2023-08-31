#pragma once
#include <string>
#include "DxLib.h"
#include "Timer.h"
#include "UIManager.h"
/// <summary>
/// �J�E���g�_�E����UI
/// </summary>
class CountDown
{
public:
    /// <summary>
    /// �J�E���g�_�E����UI
    /// </summary>
    /// <param name="setTimer">���b�v�邩</param>
    CountDown(Timer* timer);
    /// <summary>
    /// ���ɂȂ�
    /// </summary>
    ~CountDown() {};
    /// <summary>
    /// �^�C�}�[��i�܂���UI�̐�����ύX����
    /// </summary>
    void Update();
    /// <summary>
    /// �J�E���g�_�E�����I�������
    /// </summary>
    /// <returns></returns>
    bool IsCountDownEnd()const;
    /// <summary>
    /// �J�E���g�_�E���̉�����I�������
    /// </summary>
    /// <returns></returns>
    bool IsPlayCountDownSound()const;
    /// <summary>
    /// �J�E���g�_�E���̐����̕`��
    /// </summary>
    virtual void DrawUI()const;
protected:
    //�J�E���g�_�E�����I�������
    bool isCountDownEnd = false;
    //�J�E���g�_�E�����ʉ���炵����
    bool isPlayedCountSE = false;
    //�J�E���g�_�E����UI
    UIData countDownUIData;
    //�I��莞��UI
    UIData endUI;
    //�J�E���g�_�E��UI�̉摜��ύX���邽�߂̓Y����
    int uiHIndex = -1;
    //�J�E���g�_�E���𐔂���^�C�}�[
    Timer* timer;
};