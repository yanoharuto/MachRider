#pragma once
#include "Actor.h"
#include "ObjectSubject.h"
/// <summary>
/// ��s�D
/// </summary>
class FlyShip abstract:
    public Actor
{
public:
    FlyShip(ObjectInit::InitObjKind kind);
    virtual ~FlyShip();
    virtual void Update();

protected:
    //���������[�U�[�̈ʒu�Ȃǂ�������p
    ObjectSubject* sub;
};