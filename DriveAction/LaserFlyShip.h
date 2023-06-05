#pragma once
#include "FlyShip.h"

/// <summary>
/// レーザーを出す飛行船
/// </summary>
class LaserFlyShip abstract:
    public FlyShip
{
public:
    /// <summary>
    /// 初期化 目的地の方に向かせる
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos,ObjectInit::InitObjKind kind);
    /// <summary>
    /// レーザーを照射
    /// </summary>
    virtual void GenerateLaser() = 0;
protected:
    //初期位置Y
    float firstPosY;
};
