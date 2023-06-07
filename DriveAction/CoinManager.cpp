#include "CoinManager.h"
#include "Utility.h"
#include "ListUtility.h"
#include "FirstPositionGetter.h"
#include "Coin.h"
#include "Object.h"
/// <summary>
/// �R�C���̐ݒu
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
/// coinPosList�̍X�V�Ǝ��ꂽ�R�C���̍폜
/// </summary>
void CoinManager::Update()
{
    coinPosList.clear();
    Coin* coin = coinVec[0];
    if (coin->GetObjectState() != Object::ObjectState::dead)
    {
        coin->Update();
        //�R�C���̈ʒu���X�V
        coinPosList.push_back(coin->GetPos());
    }
    else 
    {
        //erase�͏������C�e���[�^�[�̎��̓z��Ԃ�
        coinVec.erase(coinVec.begin());
        brokenCoinNum++;
        SAFE_DELETE(coin);
    }
}
/// <summary>
/// �R�C���̕`��
/// </summary>
void CoinManager::Draw()const
{
    if (!coinVec.empty())
    {
        coinVec[0]->Draw();
    }
}

/// <summary>
/// �R�C���̈ʒu
/// </summary>
/// <returns></returns>
std::list<VECTOR> CoinManager::GetCoinPosList() const
{
    return coinPosList;
}
/// <summary>
/// �R�C���̏�������
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

