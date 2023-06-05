#pragma once
#include <string>
#include <list>
#include "Coin.h"
#include "ObjPosAndDir.h"
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
    void Draw();
 
    /// <summary>
    /// コインの位置
    /// </summary>
    /// <returns></returns>
    std::list<VECTOR> GetCoinPosList();
    /// <summary>
    /// コインの初期枚数
    /// </summary>
    /// <returns></returns>
    int GetCoinFirstNum();
    /// <summary>
    /// コインの現在の枚数
    /// </summary>
    /// <returns></returns>
    int GetCoinNowNum();
private:
    //コインのポジションのパス
    const std::string coinPosPass = "data/stageMap_collectPos.csv";
    //コインの最初の枚数
    int coinFirstNum;
    //コインの現在枚数
    int coinNum;
    //コインの実体リスト
    std::list<Coin*> coinList;
    //コインのポジション
    std::list<VECTOR> coinPosList;
};
