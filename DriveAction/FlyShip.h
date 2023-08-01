#pragma once
#include "Actor.h"
/// <summary>
/// 飛行船
/// </summary>
class FlyShip abstract:
    public Actor
{
public:
    /// <summary>
    /// 何かを発射する敵
    /// </summary>
    /// <param name="kind"></param>
    FlyShip(ObjectInit::InitObjKind kind);
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update()=0;

protected:
};