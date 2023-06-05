#pragma once
#include "FadeMode.h"
/// <summary>
/// ��ʂ̐؂�ւ��������
/// </summary>
class FadeInFadeOut
{
public:
    /// <summary>
    /// �t�F�[�h�C���t�F�[�h�A�E�g������
    /// </summary>
    FadeInFadeOut();
    ~FadeInFadeOut();
    /// <summary>
    /// �t�F�[�h�C���̍X�V
    /// </summary>
    void FadeIn();
    /// <summary>
    /// �t�F�[�h�A�E�g�̏���
    /// </summary>
    void FadeOutStart();
    /// <summary>
    /// �t�F�[�h�C���̏���
    /// </summary>
    void FadeInStart();
    /// <summary>
    /// �t�F�[�h�A�E�g�̍X�V
    /// </summary>
    void FadeOut();
    /// <summary>
    /// �����̍�ƒ���
    /// </summary>
    /// <returns></returns>
    FadeMode GetFadeMode();
    /// <summary>
    /// �A�E�g���Ȃ甒���Ȃ�@�C���Ȃ����̃��f���Ƃ���������
    /// </summary>
    void Draw();
private:
    //�����قǔ����Ȃ��
    float fadeValue = 0;
    //�t�F�[�h�A�E�g���鑬�x
    const float fadeSpeed = 10.0f;
    //�����̍�Ƃ��Ă��邩
    FadeMode fadeMode;
};

