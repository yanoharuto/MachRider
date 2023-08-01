#pragma once

class RankingData
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
    //std::vector<int> scoreRanking;
    
};