#pragma once
#include "UIManager.h"
#include "UserInput.h"
/// <summary>
/// ���������`�悷��
/// </summary>
class PlayManual
{
public:
    /// <summary>
    /// �摜��ǂݍ���
    /// </summary>
    PlayManual();
    ~PlayManual();
    /// <summary>
    /// �v���C���[�̓��͂ɂ���đ��������ς���
    /// </summary>
    void Update();
    /// <summary>
    /// ��������̕`��
    /// </summary>
    void Draw()const;
private:
    //�`�悷�鑀����@�f�[�^
    UIData playManualData = {};
    //������@�̉��Ɉ����g
    UIData sheatData = {};
    //�`�悵����������@
    UIKind nowUIKind = manual;
    //�e�L�[�̑�����@
    struct ButtonUI
    {
        UIData data = {};
        bool push = false;
    };
    //���{�^������UI
    ButtonUI leftBUI;
    //�E�{�^������UI
    ButtonUI rightBUI;
    //���{�^������UI
    ButtonUI downBUI;
};