#include "ResultScore.h"
#include <fstream>
#include <math.h>
#include "Utility.h"
#include "Timer.h"
#include "ObjectObserver.h"

const int ResultScore::coinBonus;
const int ResultScore::noHitScore;
const int ResultScore::timeBonus;
const int ResultScore::damageObjHitDec;
ResultScore::ResultScore(Timer* timer, std::shared_ptr<ObjectObserver> player)
{
    playerObserver = player;
    gameTimer = timer;
}


int ResultScore::GetScore(ScoreKind scoreKind) const
{
    switch (scoreKind)
    {
    case ScoreKind::time:
        return static_cast<int>(gameTimer->GetLimitTime() * timeBonus);
        break;
    case ScoreKind::hit:
        return noHitScore - playerObserver.lock()->GetSubjectHitCount(Object::ObjectTag::damageObject) * damageObjHitDec;
        break;
    case ScoreKind::collect:
        return playerObserver.lock()->GetSubjectHitCount(Object::ObjectTag::collect) * coinBonus;
        break;
    case ScoreKind::total:
        return GetScore(time) + GetScore(hit) + GetScore(collect);
        break;
    default:
        break;
    }
    return 0;
}