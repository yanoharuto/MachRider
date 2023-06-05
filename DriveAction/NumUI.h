#pragma once
#include <string>
#include "UIManager.h"
#define TIMER_FONT_NUM 10


/// <summary>
/// ������`�悷��
/// </summary>
class NumUI
{
public:
    NumUI(UIKind kind);
    ~NumUI();
    void Draw(int num);

    void Draw(float num);
    /// <summary>
    /// �ꕶ���̑傫��
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
private:
    /// <summary>
    /// ������`�悵�������p
    /// </summary>
    /// <param name="x">��ԉE�[</param>
    /// <param name="y">Y���W</param>
    /// <param name="num">����</param>
    /// <param name="scale">�����̑傫��</param>
    /// <returns>���[�̍��W</returns>
    int Draw(int x, int y, int num);
    //�����̃f�[�^
    UIData numData;
    //�����_�̉摜
    UIData pointData;
};