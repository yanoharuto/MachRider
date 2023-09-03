#include "ScoreRecordWriter.h"
#include "ResultScore.h"
/// <summary>
/// �X�V����X�R�A�̃t�@�C�����J��
/// </summary>
/// <param name="filePath">�X�R�A�̃t�@�C���̃p�X</param>
/// <param name="scoreBorder">���̃X�e�[�W�̃X�R�A�̋L�^�̐�����</param>
ScoreRecordWriter::ScoreRecordWriter(std::string filePath, InitStage::ScoreBorder scoreBorder)
{
    border = scoreBorder;
    // �t�@�C�����J����
    writing_file.open(filePath, std::ios::out);
}
/// <summary>
/// �X�R�A�̋L�^�̍X�V
/// </summary>
/// <param name="score">���ݗV��ł���X�e�[�W�̋L�^�������Ă��炤</param>
void ScoreRecordWriter::UpdateScoreRecord(ResultScore* const resultScore)
{
    //��؂蕶��
    std::string colon = ",";
    //�X�R�A�̐�����������
    std::string borderString = std::to_string(border.gold) + colon + std::to_string(border.silver) + colon + std::to_string(border.bronze) + colon;
    //�X�R�A�̃����L���O������
    std::string updateString;
    std::string highScoreStr = resultScore->GetHighScoreString();
    int highScore = atoi(highScoreStr.c_str());
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
        //�X�R�A�̍X�V
        writing_file << borderString + updateString << std::endl;
    }
}
