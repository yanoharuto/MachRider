#pragma once
#include <vector>
class RankingData
{
public:
    RankingData();

    ~RankingData();
    void UpdateRanking(int score);
private:
    std::vector<int> scoreRanking;
    
};