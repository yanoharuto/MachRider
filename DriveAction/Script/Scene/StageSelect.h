#pragma once
#include "UIManager.h"

/// <summary>
/// �^�C�g����ʂŃX�e�[�W�I�Ԏ��Ɏg��
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// �X�e�[�W�I��UI�̓ǂݍ���
    /// ��ԍŏ��̃X�e�[�W�ɕύX
    /// </summary>
    StageSelect();
    /// <summary>
    /// UI�̍폜
    /// </summary>
    ~StageSelect();
    /// <summary>
    /// �\���L�[�ŗV�ԃX�e�[�W�ύX
    /// </summary>
    void Update();
    /// <summary>
    /// ���ݑI��ł���X�e�[�W��\��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// �X�e�[�W�̔ԍ�����
    /// </summary>
    /// <returns>���I�����Ă���X�e�[�W�̔ԍ�</returns>
    int GetSelectStageNum()const;
private:
    //�X�e�[�W�ԍ�
    int selectStageNum;
    //�I�����Ă���X�e�[�W���������\��
    const float selectSizeCoefficient = 1.4f;
    //�I��ł���X�e�[�W�̖��O��\��
    UIData stageNameUIData;
    //�X�e�[�W�����肷��Ƃ��̃{�^����\��
    UIData selectButtonUIData;
};

