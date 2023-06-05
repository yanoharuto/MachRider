#pragma once
#include <string>
#include <vector>
#include "FirstPositionGetter.h"
class StageManager;
class ChallengeFlow
{
public:
    ChallengeFlow();
    ~ChallengeFlow();
private:
    std::string challengeListPass;
    std::vector<ChallengeData> challengeDataVec;
};

