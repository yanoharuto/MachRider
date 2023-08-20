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
    //�������Ԃ𒴉߂��Ă���0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetRemainingTime() * clearTimeBonus);
    //���W�A�C�e��������Ă���{�[�i�X
    collectScore= player.lock()->GetCollectCount() * getCollectBonus;
    //������ߋ��̃n�C�X�R�A��葽��������True
    isUpdateHiScore = timeScore + collectScore > StageDataManager::GetScoreBorder().highScore;
    //�X�R�A�̍X�V
    StageDataManager::SaveHiScore(timeScore + collectScore);
}
/// <summary>
/// �n�C�X�R�A���X�V���ꂽ��
/// </summary>
/// <returns>�n�C�X�R�A���X�V����Ă�����True</returns>
bool ResultScore::IsUpdateHiScore()
{
    return isUpdateHiScore;
}
