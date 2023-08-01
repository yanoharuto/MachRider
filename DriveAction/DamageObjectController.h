#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "ActorController.h"

class ObjectObserver;
/// <summary>
/// ダメージ判定のあるオブジェクトの操作親クラス
/// </summary>
class DamageObjectController abstract:
    public ActorController
{
public:
    /// <summary>
    /// ダメージ判定のあるオブジェクト
    /// </summary>
    /// <param name="kind"></param>
    DamageObjectController(ObjectInit::InitObjKind kind)
    :ActorController(kind)
    {};
    virtual void AddObject(std::unique_ptr<ObjectObserver> sub) = 0;
protected:
};

