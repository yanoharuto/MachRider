#pragma once
#include "NumUI.h"
/// <summary>
/// �^�C�g���ŕ\������n�C�X�R�A
/// </summary>
class TitleHiScore:private NumUI
{
public:
    /// <summary>
    /// �^�C�g���ŕ\������n�C�X�R�A
    /// </summary>
    TitleHiScore();
    /// <summary>
    /// ���ɂȂ�
    /// </summary>
    ~TitleHiScore() {};
    /// <summary>
    /// ���ݑI�΂�Ă���X�e�[�W�̃n�C�X�R�A�\��
    /// </summary>
    void Draw()const;

private:
    //�e�X�e�[�W�̃n�C�X�R�A
    UIData hiScoreUI;
};

