#pragma once
#include "DxLib.h"
#include "Actor.h"
/// <summary>
/// アイテムの効果を発揮するときに必要
/// </summary>
struct  ItemArgumentCarInfo
{
    //車の位置
    VECTOR position;
    //車の向き
    VECTOR direction;
    //車の速さ
    VECTOR velocity;
    //車の半径
    float radius;
    void SetCarInfo(Actor* actor)
    {
        position = actor->GetPos();
        direction = actor->GetDir();
        velocity = actor->GetVelocity();
        radius = actor->GetRadius();
    }
};