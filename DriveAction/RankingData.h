#pragma once
#include "StageDataPass.h"

class RankingData:StageDataPass
{
public:
    RankingData();

    ~RankingData();
    /// <summary>
    /// 3�ʈȏ�Ȃ烉���L���O���X�V
    /// </summary>
    /// <param name="score"></param>
    void UpdateRanking(int score);
private:
    std::vector<int> scoreRanking;
    
};