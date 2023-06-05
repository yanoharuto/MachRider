#pragma once
#include "DxLib.h"
#include "Actor.h"
/// <summary>
/// �A�C�e���̌��ʂ𔭊�����Ƃ��ɕK�v
/// </summary>
struct  ItemArgumentCarInfo
{
    //�Ԃ̈ʒu
    VECTOR position;
    //�Ԃ̌���
    VECTOR direction;
    //�Ԃ̑���
    VECTOR velocity;
    //�Ԃ̔��a
    float radius;
    void SetCarInfo(Actor* actor)
    {
        position = actor->GetPos();
        direction = actor->GetDir();
        velocity = actor->GetVelocity();
        radius = actor->GetRadius();
    }
};