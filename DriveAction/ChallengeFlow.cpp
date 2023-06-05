#include "ChallengeFlow.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include "FirstPositionGetter.h"

ChallengeFlow::ChallengeFlow()
{
    challengeDataVec = FirstPositionGetter::GetChallengeData();
}

ChallengeFlow::~ChallengeFlow()
{
}
