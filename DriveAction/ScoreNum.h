#pragma once
#include "NumUI.h"
#include "DxLib.h"
/// <summary>
/// ���v�X�R�A�̕\��
/// </summary>
class ScoreNum :
    public NumUI
{
public:
    ScoreNum();
    ~ScoreNum();
    /// <summary>
    /// �X�R�A�ɂ���đ傫���ύX
    /// </summary>
    /// <param name="num"></param>
    void Draw(int num)const override;
private:
    //���ɃN���A�����Ƃ��̃X�R�A�̃��C��
    int first = 0;
    //���ʂɃN���A�����Ƃ��̃X�R�A�̃��C��
    int second = 0;
    //�Ȃ�Ƃ��N���A�����Ƃ��̃X�R�A�̃��C��
    int third = 0;
    //second����̃X�R�A�ɂȂ������̕����̃t�H���g
    float secondBorderFontSize = 0.9f;
    //third����̃X�R�A�ɂȂ������̕����̃t�H���g
    float thirdBorderFontSize = 0.85f;
    //third��艺�̃X�R�A�ɂȂ������̕����̃t�H���g
    float thirdUnderFontSize = 0.8f;

    VECTOR firstColor = VGet(255,215,0);
    VECTOR secondColor = VGet(192,192,192);
    VECTOR thirdColor = VGet(196,112,34);
    VECTOR thirdUnderColor = VGet(176,92,14);
};

