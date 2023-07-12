#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "InitActor.h"
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
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
    EnemyGenerator();

    ~EnemyGenerator() {};
    /// <summary>
    /// �����̃}�l�[�W���[�ɓZ�߂ē��������n���Ă���
    /// </summary>
    /// <param name="controllerManager"></param>
    void CreateEnemy(ActorControllerManager* controllerManager);
    
private:
    /// <summary>
    /// �G�@��Z�߂ē������z���쐬
    /// </summary>
    /// <param name="kind"></param>
    /// <param name="generatePosMap"></param>
    /// <param name="controllerManager"></param>
    void CreateActorController(InitObjKind kind, std::unordered_map<int, std::vector<VECTOR>> generatePosMap, ActorControllerManager* controllerManager);
    //�X�e�[�W�ɔz�u�����A�C�e���̍ő吔
    int totalCollectNum = 0;
    //���Ԗڂ̎��W�A�C�e����
    int collectNum = -1;
    //�G�̈ʒu�܂Ƃ�
    std::vector<InitStage::ChallengeData> challengeDataVec;
};