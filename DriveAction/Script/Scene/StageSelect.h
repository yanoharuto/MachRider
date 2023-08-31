#pragma once
#include "UIManager.h"

/// <summary>
/// �^�C�g����ʂŃX�e�[�W�I�Ԏ��Ɏg��
/// </summary>
class StageSelect
{
public:
    /// <summary>
    /// �X�e�[�W���ƂɕK�v�ȃA�Z�b�g�̃A�h���X��
    /// �����Ă���t�@�C����
    /// �A�h���X�������Ă���t�@�C����ǂݍ���
    /// </summary>
    /// <returns></returns>
    StageSelect();
    /// <summary>
    /// �V�ԃX�e�[�W�ύX����Ƃ��Ɏg��
    /// </summary>
    /// <param name="next">���̃X�e�[�WTrue�O�̃X�e�[�W��false</param>
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
    UIData stageNameUI;
    //�X�e�[�W�����肷��Ƃ��̃{�^����\��
    UIData selectButtonUI;
};

