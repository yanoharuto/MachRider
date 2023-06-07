#pragma once
#include <string>
#include <list>
#include <vector>
#include "DxLib.h"
class Coin;
/// <summary>
/// �ʒu���~�j�}�b�v�ɋ������肷��
/// </summary>
class CoinManager
{
public:
    /// <summary>
    /// �R�C���̐ݒu
    /// </summary>
    CoinManager();
    ~CoinManager();
    /// <summary>
    /// coinPosList�̍X�V�Ǝ��ꂽ�R�C���̍폜
    /// </summary>
    void Update();
    /// <summary>
    /// �R�C���̕`��
    /// </summary>
    void Draw()const;
 
    /// <summary>
    /// �R�C���̈ʒu
    /// </summary>
    /// <returns></returns>
    std::list<VECTOR> GetCoinPosList() const;

    /// <summary>
    /// �R�C���̏�������
    /// </summary>
    /// <returns></returns>
    int GetCoinFirstNum() const;

    int GetRemainingCoin();
private:
    //�R�C���̍ŏ��̖���
    int coinFirstNum;
    int brokenCoinNum;
    //�R�C���̃��X�g
    std::vector<Coin*> coinVec;
    //�R�C���̃|�W�V����
    std::list<VECTOR> coinPosList;
};
