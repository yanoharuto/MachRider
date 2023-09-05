#include "ScoreRecordWriter.h"
#include "ResultScore.h"
/// <summary>
/// �X�R�A�̋L�^������
/// </summary>
/// <param name="filePath">�X�R�A�̃t�@�C���̃p�X</param>
/// <param name="scoreBorder">���̃X�e�[�W�̃X�R�A�̋L�^�̐�����</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, InitStage::ScoreBorder scoreBorder)
{
    //CSV�t�@�C���̋�؂蕶��
    std::string colon = ",";
    scoreRecordFilePath = filePath;
    border = scoreBorder;
    //�ύX���Ȃ��������̉ӏ�
    borderString = std::to_string(scoreBorder.gold) + colon + std::to_string(scoreBorder.silver) + colon + std::to_string(scoreBorder.bronze) + colon;
}
/// <summary>
/// �X�R�A�̋L�^�̍X�V
/// </summary>
/// <param name="score">���ݗV��ł���X�e�[�W�̋L�^�������Ă��炤</param>
void ScoreRecordWriter::UpdateScoreRecord(ResultScore* const resultScore)
{
    //�ō��X�R�A
    int highScore = resultScore->GetUpdateScore();
    //CSV�t�@�C���̋�؂蕶��
    std::string colon = ",";
    //�X�R�A�̃����L���O������
    std::string updateString;
    //�n�C�X�R�A�̕�����
    std::string highScoreStr = std::to_string(highScore);
    //�n�C�X�R�A�����L���O1�ʂ̍X�V
    if (border.highScore < highScore)
    {
        updateString = highScoreStr + colon + std::to_string(border.highScore) + colon + std::to_string(border.second) + colon;
    }
    //2�ʂ̍X�V
    else if (border.second < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + highScoreStr + colon + std::to_string(border.second) + colon;
    }
    //3�ʂ̍X�V
    else if (border.third < highScore)
    {
        updateString = std::to_string(border.highScore) + colon + std::to_string(border.second) + colon + highScoreStr + colon;
    }
    //�X�R�A�X�V�L��Ȃ珑������
    if (!updateString.empty())
    {
        // �t�@�C�����J����
        std::ofstream writing_file;
        writing_file.open(scoreRecordFilePath, std::ios::out);
        //�X�R�A�̍X�V
        writing_file << borderString + updateString << std::endl;
        //�������ݏI��
        writing_file.close();
    }
}