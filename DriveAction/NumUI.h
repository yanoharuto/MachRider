#pragma once
#include <string>
#include "UIManager.h"
#define TIMER_FONT_NUM 10


/// <summary>
/// ������`�悷��@������
/// </summary>
class NumUI
{
public:
    NumUI(UIKind kind);
    ~NumUI();
    /// <summary>
    /// �����̕`��
    /// </summary>
    /// <param name="num"></param>
    virtual void Draw(int num)const;
    /// <summary>
    /// �����̕`��@�����_�t��
    /// </summary>
    /// <param name="num"></param>
    void Draw(float num) const;
    /// <summary>
    /// ���S���WX
    /// </summary>
    /// <returns></returns>
    int GetX()const { return numData.x; };
    /// <summary>
    /// ���S���WY
    /// </summary>
    /// <returns></returns>
    int GetY()const { return numData.y; };
    /// <summary>
    /// �ꕶ���̑傫��
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
protected:
    /// <summary>
    /// �����̕`��
    /// </summary>
    /// <param name="x">��ԉE�[</param>
    /// <param name="y">Y���W</param>
    /// <param name="num">����</param>
    /// <param name="scale">�����̑傫��</param>
    /// <returns>���[�̍��W</returns>
    int Draw(UIData data, int num)const;
    //�����̃f�[�^
    UIData numData;
    //�����_�̉摜
    UIData pointData;
};