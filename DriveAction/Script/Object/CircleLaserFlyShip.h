#pragma once
#include<iostream>
#include<memory>
#include "Actor.h"
class DamageObjectGenerator;
/// <summary>
/// �~��ɐw�`��g�݃��[�U�[�𔭎˂����s�D
/// </summary>
class CircleLaserFlyShip : public Actor
{
public:
    /// <summary>
    /// �ʒu�ƌ��������������ă��[�U�[�𔭎�
    /// </summary>
    /// <param name="setPos">�ʒu</param>
    /// <param name="setDestinationPos">�����ׂ������̈ʒu</param>
    /// <param name="damageObjectGenerator">���[�U�[�𔭎˂��邱�Ƃ�`����N���X</param>
    CircleLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos,std::weak_ptr<DamageObjectGenerator> damageObjectGenerator);
};

