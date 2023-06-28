#include "ResultScore.h"
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"

const int ResultScore::coinBonus;
const int ResultScore::noHitScore;
const int ResultScore::timeBonus;
const int ResultScore::damageObjHitDec;
int ResultScore::collectScore = 0;
int ResultScore::timeScore = 0;
bool ResultScore::noHit = false;

/// <summary>
/// �X�R�A����
/// </summary>
/// <param name="scoreKind">�ǂ̃X�R�A���~������</param>
/// <returns></returns>
int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ResultScore::time:
        return timeScore;
        break;
    case ResultScore::collect:
        return collectScore;
        break;
    case ResultScore::hit:
        return noHit ? noHitScore : 0;
        break;
    case ResultScore::total:
        return timeScore + collectScore + GetScore(hit);
        break;
    }
}
/// <summary>
/// �X�R�A���m�肳����
/// </summary>
/// <param name="timer"></param>
/// <param name="player"></param>
void ResultScore::FixScore(Timer* timer, std::weak_ptr<ObjectObserver> player)
{
    //�������Ԃ𒴉߂��Ă���0
    timeScore = timer->IsOverLimitTime() ? 0 : static_cast<int>(timer->GetElaspedTime() * timeBonus);
    //���W�A�C�e��������Ă���{�[�i�X
    collectScore= player.lock()->GetSubjectHitCount(Object::ObjectTag::collect) * coinBonus;
    //
    noHit = player.lock()->GetSubjectHitCount(Object::ObjectTag::damageObject) == 0;
}