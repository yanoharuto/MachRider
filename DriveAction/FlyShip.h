#pragma once
#include "Actor.h"
#include "ObjectSubject.h"
/// <summary>
/// 飛行船
/// </summary>
class FlyShip abstract:
    public Actor
{
public:
    FlyShip(ObjectInit::InitObjKind kind);
    virtual ~FlyShip();
    virtual void Update();

protected:
    //撃ったレーザーの位置などを教える用
    ObjectSubject* sub;
};