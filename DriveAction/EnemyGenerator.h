#pragma once
#include <vector>
#include <unordered_map>
#include "InitActor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
class UpDownFlyShipController;
class CircleFlyShipController;
class BomberFlyShipController;
class SawController;
class ActorController;
class ActorControllerManager;
using namespace ObjectInit;
/// <summary>
/// �G�@�̐������s��
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
    /// �G�@�ʒu�ɂ��Ă̏���������
    /// </summary>
    EnemyGenerator();

    ~EnemyGenerator() {};
    /// <summary>
    /// �G�l�~�[�𐶐�
    /// </summary>
    /// <param name="collectNum">���v���C���[�͉��ڂ̎��W�A�C�e�����������</param>
    void GenerateEnemys(int collectNum,ActorController* const addObjController);
private:
    /// <summary>
    /// �G�l�~�[�̔z�u��������
    /// </summary>
    /// <param name="kind">�ǂ̎�ނ�</param>
    /// <param name="collectNum">���Ԗڂ̎��W�A�C�e���̎���</param>
    /// <returns>kind�̃G�l�~�[�̔z�u���</returns>
    std::vector<EditArrangementData> GetNowEnemyEditData(int collectNum);
    
    //�G�̈ʒu�܂Ƃ�
    std::vector<EditArrangementData> editDataVec;
};