#include "CoinManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "Object.h"
/// <summary>
/// コインの設置
/// </summary>
CoinManager::CoinManager()
{
    auto challengeVec = FirstPositionGetter::GetChallengeData();
    coinFirstNum = challengeVec.size();
    for (int i = 0; i < coinFirstNum; i++)
    {
        Coin* newCoin = new Coin(challengeVec[i].collectPos[0][0]);
        coinVec.push_back(newCoin);
    }
}

CoinManager::~CoinManager()
{
    for (auto ite = coinVec.begin(); ite != coinVec.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    coinVec.clear();
}
/// <summary>
/// coinPosListの更新と取られたコインの削除
/// </summary>
void CoinManager::Update()
{
    coinPosList.clear();
    Coin* coin = coinVec[0];
    if (coin->GetObjectState() != Object::ObjectState::dead)
    {
        coin->Update();
        //コインの位置を更新
        coinPosList.push_back(coin->GetPos());
    }
    else 
    {
        //eraseは消したイテレーターの次の奴を返す
        coinVec.erase(coinVec.begin());
        brokenCoinNum++;
        SAFE_DELETE(coin);
    }
}
/// <summary>
/// コインの描画
/// </summary>
void CoinManager::Draw()const
{
    if (!coinVec.empty())
    {
        coinVec[0]->Draw();
    }
}

/// <summary>
/// コインの位置
/// </summary>
/// <returns></returns>
std::list<VECTOR> CoinManager::GetCoinPosList() const
{
    return coinPosList;
}
/// <summary>
/// コインの初期枚数
/// </summary>
/// <returns></returns>
int CoinManager::GetCoinFirstNum() const
{
    return coinFirstNum;
}

int CoinManager::GetRemainingCoin()
{
    return coinVec.size();
}

