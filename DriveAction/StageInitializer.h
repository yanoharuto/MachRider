#pragma once
#include <iostream>
#include <memory>
#include "StageDataPass.h"
class ActorControllerManager;
class ObjectObserver;

/// <summary>
/// ステージの初期化
/// </summary>
class StageInitializer :StageDataPass
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageInitializer();
    ~StageInitializer();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="cotrollerManager"></param>
    void Init(ActorControllerManager* cotrollerManager);
    /// <summary>
    /// プレイヤーの位置等を教えてくれるやつを出す
    /// </summary>
    /// <returns></returns>
    std::weak_ptr<ObjectObserver> GetPlayerObserver()const;
    /// <summary>
    /// ステージの制限時間
    /// </summary>
    /// <returns></returns>
    float GetGameTime()const;
private:
    //プレイヤーの位置等を教えてくれるやつ
    std::weak_ptr<ObjectObserver> playerObserver;
};