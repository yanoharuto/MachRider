#pragma once
#include "StageDataPass.h"

class RankingData:StageDataPass
{
public:
    RankingData();

    ~RankingData();
    /// <summary>
    /// 3位以上ならランキングを更新
    /// </summary>
    /// <param name="score"></param>
    void UpdateRanking(int score);
private:
    std::vector<int> scoreRanking;
    
};