#pragma once
#include <vector>
#include <string>

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
    ~StageSelect();
    /// <summary>
    /// �V�ԃX�e�[�W�ύX����Ƃ��Ɏg��
    /// </summary>
    /// <param name="next">���̃X�e�[�WTrue�O�̃X�e�[�W��false</param>
    void Update();
    /// <summary>
    /// �ǂ̃X�e�[�W��I��ł��邩
    /// </summary>
    /// <returns></returns>
    static std::string GetLoadeStageName();
private:
    int dataNum;
    //�X�e�[�W�̈ꗗ�I�ȓz
    std::string allStageAddresFile = "data/stageData/stageDataList.csv";

    std::vector<std::string> dataLoader;
    //�e�X�e�[�W�̃f�[�^�̃p�X
    static std::string fileAddres;
};

