#pragma once
#include <string>
#include <list>
#include "Coin.h"
#include "ObjPosAndDir.h"
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
    void Draw();
 
    /// <summary>
    /// �R�C���̈ʒu
    /// </summary>
    /// <returns></returns>
    std::list<VECTOR> GetCoinPosList();
    /// <summary>
    /// �R�C���̏�������
    /// </summary>
    /// <returns></returns>
    int GetCoinFirstNum();
    /// <summary>
    /// �R�C���̌��݂̖���
    /// </summary>
    /// <returns></returns>
    int GetCoinNowNum();
private:
    //�R�C���̃|�W�V�����̃p�X
    const std::string coinPosPass = "data/stageMap_collectPos.csv";
    //�R�C���̍ŏ��̖���
    int coinFirstNum;
    //�R�C���̌��ݖ���
    int coinNum;
    //�R�C���̎��̃��X�g
    std::list<Coin*> coinList;
    //�R�C���̃|�W�V����
    std::list<VECTOR> coinPosList;
};
