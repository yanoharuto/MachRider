#pragma once
#include<iostream>
#include<memory>
#include "Actor.h"
class DamageObjectGenerator;
/// <summary>
/// 円状に陣形を組みレーザーを発射する飛行船
/// </summary>
class CircleLaserFlyShip : public Actor
{
public:
    /// <summary>
    /// 位置と向きを初期化してレーザーを発射
    /// </summary>
    /// <param name="setPos">位置</param>
    /// <param name="setDestinationPos">向くべき方向の位置</param>
    /// <param name="damageObjectGenerator">レーザーを発射することを伝えるクラス</param>
    CircleLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos,std::weak_ptr<DamageObjectGenerator> damageObjectGenerator);
};

