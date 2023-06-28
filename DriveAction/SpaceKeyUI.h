#pragma once

#include "UIManager.h"
/// <summary>
/// spaceKey�̍Ñ�
/// </summary>
class SpaceKeyUI
{
public:
    SpaceKeyUI(int setX,int setY);
    ~SpaceKeyUI();
    /// <summary>
    /// �A���t�@�l�̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// ���X�ɔ����Ȃ�����Z���Ȃ����肵�Ȃ���`��
    /// </summary>
    void Draw()const;
private:
    //�X�y�[�X�L�[UI
    UIData pressKeyData;
    //�A���t�@�l
    int aValue;
    //�A���t�@�l�̑������x
    const int aSpeed = 10;
    //�A���t�@�l�̍Œ�l
    const int lowtestAvalue = 60;
    //�A���t�@�l�𑝂₷���ǂ���
    bool isAValueIncrement = false;
};