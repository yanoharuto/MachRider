#pragma once
#include "UIManager.h"
#include "StageDataPass.h"
/// <summary>
/// �^�C�g����ʂŃX�e�[�W�I�Ԏ��Ɏg��
/// </summary>
class StageSelect :public StageDataPass
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
private:
    //�X�e�[�W�ԍ�
    int stageNum;
    //�I��ł���X�e�[�W�̖��O��\��
    UIData stageNameData;
    //�X�e�[�W�����肷��Ƃ��̃{�^����\��
    UIData selectButtonData;
};

