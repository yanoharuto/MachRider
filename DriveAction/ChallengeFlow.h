#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include "DxLib.h"
#include "InitObjKind.h"
#include "FirstPositionGetter.h"
class StageInitializer;
class ObjectObserver;
class ActorControllerManager;
class EnemyGenerator;
/// <summary>
/// �Q�[���̉ۑ�̐i�s�Ǘ�
/// </summary>
class ChallengeFlow
{
public:
    ChallengeFlow(std::weak_ptr<ObjectObserver> player);
    ~ChallengeFlow();

    /// <summary>
    /// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̐�
    /// </summary>
    /// <returns></returns>
    int GetTotalCollectNum();

    /// <summary>
    /// �v���C���[���W�߂Ȃ���΂����Ȃ��A�C�e���̎c���Ă��鐔
    /// </summary>
    /// <returns></returns>
    bool IsEndingChallenge();

    /// <summary>
    /// �v���C���[���A�C�e�������������controllerManager���X�V
    /// </summary>
    /// <param name="controllerManager"></param>
    void Update(ActorControllerManager* controllerManager);
private:
    /// <summary>
    /// �v���C���[���A�C�e�������������G�l�~�[�ǉ�
    /// </summary>
    /// <param name="objTag"></param>
    /// <param name="controllerManager"></param>
    void AddEnemyController(ObjectInit::InitObjKind objTag, ActorControllerManager* controllerManager);
    int totalCollectNum = 0;
    int collectNum = -1;
    std::vector<InitStage::ChallengeData> challengeDataVec;
    //���L�����Ȃ����L�|�C���^
    std::weak_ptr<ObjectObserver> playerObserver;

    EnemyGenerator* enemyCreator;
};


