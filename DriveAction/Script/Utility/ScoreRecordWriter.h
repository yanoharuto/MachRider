#pragma once
#include <fstream>
#include "StageDataManager.h"
class ResultScore;
/// <summary>
/// �X�R�A���X�V���ăt�@�C���ɏ����ڂ�
/// </summary>
class ScoreRecordWriter
{
public:
    /// <summary>
    /// �X�V����X�R�A�̃t�@�C�����J��
    /// </summary>
    /// <param name="filePath">�X�R�A�̃t�@�C���̃p�X</param>
    /// <param name="scoreBorder">���̃X�e�[�W�̃X�R�A�̋L�^�̐�����</param>
    ScoreRecordWriter(std::string filePath,InitStage::ScoreBorder scoreBorder);
    /// <summary>
    /// �X�R�A�̋L�^�̍X�V
    /// </summary>
    /// <param name="score">���ݗV��ł���X�e�[�W�̋L�^�������Ă��炤</param>
    void UpdateScoreRecord(ResultScore* const score);
private:
    //�V��ł���X�e�[�W�̃X�R�A�̋L�^�̐�����
    ScoreBorder border;
    //�������ރt�@�C��
    std::ofstream writing_file;
};
