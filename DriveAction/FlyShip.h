#pragma once
#include "Actor.h"
/// <summary>
/// ��s�D
/// </summary>
class FlyShip abstract:
    public Actor
{
public:
    /// <summary>
    /// �����𔭎˂���G
    /// </summary>
    /// <param name="kind"></param>
    FlyShip(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update()=0;

protected:
};