#pragma once
#include "FadeMode.h"
/// <summary>
/// ��ʂ̐؂�ւ��������
/// </summary>
class FadeInFadeOut
{
public:
    /// <summary>
    /// �t�F�[�h�C���̍X�V
    /// </summary>
    static void FadeIn();
    /// <summary>
    /// �t�F�[�h�A�E�g�̍X�V
    /// </summary>
    static void FadeOut();

    /// <summary>
    /// �A�E�g���Ȃ甒���Ȃ�@�C���Ȃ����̃��f���Ƃ���������
    /// </summary>
    static void Fading();
private:
    /// <summary>
    /// �t�F�[�h�C���t�F�[�h�A�E�g������
    /// </summary>
    FadeInFadeOut();
    ~FadeInFadeOut();
    //�����قǔ����Ȃ��
    static int fadeValue;
    //�t�F�[�h�A�E�g���鑬�x
    static const int fadeSpeed;
};

