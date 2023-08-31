#include <fstream>
#include <sstream>
#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "PlayerObserver.h"
#include "StageDataManager.h"

//���W�A�C�e���Q�b�g�{�[�i�X
const int ResultScore::getCollectBonus = 500;
//�c�莞�Ԃ̃{�[�i�X
const int ResultScore::clearTimeBonus = 50;
/// <summary>
/// �Q�[���N���A�����Ƃ��̃X�R�A���v�Z����
/// </summary>
/// <param name="timer">�N���A�^�C��</param>
/// <param name="player">�N���A�����v���C���[�̏��ʒB��</param>
ResultScore::ResultScore(Timer* timer, std::weak_ptr<PlayerObserver> player)
{
    FixScore(timer, player);
}

/// <summary>
/// �X�R�A����
/// </summary>
/// <param name="scoreKind">�~�����X�R�A�̎��</param>
/// <returns>�����̃X�R�A��</returns>
int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ResultScore::timeBonus:
        return timeScore;
        break;
    case ResultScore::collectBonus:
        return collectScore;
        break;
    case ResultScore::total:
        return timeScore + collectScore;
        break;
    }
}
/// <summary>
/// �X�R�A�̔{��������
/// </summary>
/// <param name="scoreKind">�~�����X�R�A�̎��</param>
/// <returns>�����̃X�R�A�̔{��</returns>
int ResultScore::GetScoreBonus(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ResultScore::timeBonus:
        return clearTimeBonus;
        break;
    case ResultScore::collectBonus:
        return getCollectBonus;
        break;
    default:
        return -1;
        break;
    }
}
/// <summary>
/// �X�R�A���m�肳����
/// </summary>
/// <param name="timer">�N���A�^�C������</param>
/// <param name="player">�v���C���[�̏����������W�A�C�e���𒲂ׂ�</param>
void ResultScore::FixScore(Timer* const timer, std::weak_ptr<PlayerObserver> player)
{
    ScoreBorder score = StageDataManager::GetScoreBorder();
    //�������Ԃ𒴉߂��Ă���0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetRemainingTime() * clearTimeBonus);
    //���W�A�C�e��������Ă���{�[�i�X
    collectScore= player.lock()->GetCollectCount() * getCollectBonus;
    //���_
    int highScore = timeScore + collectScore;
    //������ߋ��̃n�C�X�R�A��葽��������True
    isUpdateHighScore = timeScore + collectScore > score.highScore;
    //�n�C�X�R�A�X�V�Ȃ�f�[�^������������
    if(isUpdateHighScore)
    {
        //��؂蕶��
        std::string colon = ",";
        //�X�R�A�̐�����������
        std::string borderString = std::to_string(score.gold) + colon + std::to_string(score.silver) + colon + std::to_string(score.bronze) + colon;
        //�X�R�A�̃����L���O������
        std::string updateString;
        //�n�C�X�R�A�����L���O1�ʂ̍X�V
        if (score.highScore < highScore)
        {
            updateString = std::to_string(highScore) + colon + std::to_string(score.highScore) + colon + std::to_string(score.second) + colon;
        }
        //2�ʂ̍X�V
        else if (score.second < highScore)
        {
            updateString = std::to_string(score.highScore) + colon + std::to_string(highScore) + colon + std::to_string(score.second) + colon;
        }
        //3�ʂ̍X�V
        else if (score.third < highScore)
        {
            updateString = std::to_string(score.highScore) + colon + std::to_string(score.second) + colon + std::to_string(highScore) + colon;
        }
        //�X�R�A�X�V�L��Ȃ珑������
        if (!updateString.empty())
        {
            std::ofstream writing_file;
            //�X�e�[�W�̃X�R�A���܂Ƃ߂��t�@�C���̃p�X
            std::string filePass = StageDataManager::GetSelectStageData(stageScoreFilePass);
            // �t�@�C�����J����
            writing_file.open(filePass, std::ios::out);
            //�X�R�A�̍X�V
            writing_file << borderString + updateString << std::endl;
        }
    }
}
/// <summary>
/// �n�C�X�R�A���X�V���ꂽ��
/// </summary>
/// <returns>�n�C�X�R�A���X�V����Ă�����True</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHighScore;
}
