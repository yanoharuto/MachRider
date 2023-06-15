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
/// ゲームの課題の進行管理
/// </summary>
class ChallengeFlow
{
public:
    ChallengeFlow(std::weak_ptr<ObjectObserver> player);
    ~ChallengeFlow();

    /// <summary>
    /// プレイヤーが集めなければいけないアイテムの数
    /// </summary>
    /// <returns></returns>
    int GetTotalCollectNum();

    /// <summary>
    /// プレイヤーが集めなければいけないアイテムの残っている数
    /// </summary>
    /// <returns></returns>
    bool IsEndingChallenge();

    /// <summary>
    /// プレイヤーがアイテムを回収したらcontrollerManagerを更新
    /// </summary>
    /// <param name="controllerManager"></param>
    void Update(ActorControllerManager* controllerManager);
private:
    /// <summary>
    /// プレイヤーがアイテムを回収したらエネミー追加
    /// </summary>
    /// <param name="objTag"></param>
    /// <param name="controllerManager"></param>
    void AddEnemyController(ObjectInit::InitObjKind objTag, ActorControllerManager* controllerManager);
    int totalCollectNum = 0;
    int collectNum = -1;
    std::vector<InitStage::ChallengeData> challengeDataVec;
    //所有権がない共有ポインタ
    std::weak_ptr<ObjectObserver> playerObserver;

    EnemyGenerator* enemyCreator;
};


