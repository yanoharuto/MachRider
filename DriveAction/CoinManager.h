#pragma once
#include <string>
#include <list>
#include <vector>
#include "DxLib.h"
class Coin;
/// <summary>
/// 位置をミニマップに教えたりする
/// </summary>
class CoinManager
{
public:
    /// <summary>
    /// コインの設置
    /// </summary>
    CoinManager();
    ~CoinManager();
    /// <summary>
    /// coinPosListの更新と取られたコインの削除
    /// </summary>
    void Update();
    /// <summary>
    /// コインの描画
    /// </summary>
    void Draw()const;
 
    /// <summary>
    /// コインの位置
    /// </summary>
    /// <returns></returns>
    std::list<VECTOR> GetCoinPosList() const;

    /// <summary>
    /// コインの初期枚数
    /// </summary>
    /// <returns></returns>
    int GetCoinFirstNum() const;

    int GetRemainingCoin();
private:
    //コインの最初の枚数
    int coinFirstNum;
    int brokenCoinNum;
    //コインのリスト
    std::vector<Coin*> coinVec;
    //コインのポジション
    std::list<VECTOR> coinPosList;
};
