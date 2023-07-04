#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "HitCountObserver.h"
//���W�A�C�e���Q�b�g�{�[�i�X
const int ResultScore::getCollectBonus = 500;
//�c�莞�Ԃ̃{�[�i�X
const int ResultScore::clearTimeBonus = 10;

/// <summary>
/// �X�R�A����
/// </summary>
/// <param name="scoreKind">�ǂ̃X�R�A���~������</param>
/// <returns></returns>
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
/// <param name="scoreKind"></param>
/// <returns></returns>
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
/// <param name="timer"></param>
/// <param name="player"></param>
void ResultScore::FixScore(Timer* timer, std::weak_ptr<HitCountObserver> player)
{
    //�������Ԃ𒴉߂��Ă���0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetElaspedTime() * clearTimeBonus);
    //���W�A�C�e��������Ă���{�[�i�X
    collectScore= player.lock()->GetSubjectHitCount(Object::ObjectTag::collect) * getCollectBonus;
 
}