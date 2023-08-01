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
/// �G�@�̃}�l�[�W���[
/// </summary>
class EnemyGenerator
{
public:
    /// <summary>
    /// �G�@�̏���������
    /// </summary>
    EnemyGenerator(ActorControllerManager* controllerManager);

    ~EnemyGenerator() {};
    
    void GenerateEnemys(int collectNum);
private:
    std::vector<EditArrangementData> GetNowEnemyEditData(InitObjKind kind, int collectNum);
    
    //�G�̈ʒu�܂Ƃ�
    std::vector<EditArrangementData> editDataVec;
    std::unordered_map<InitObjKind,ActorController*> enemyMap;
};