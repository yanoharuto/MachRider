#pragma once
#include "Saw.h"
#include "EditObjectData.h"
class ReusableTimer;
class SphereHitChecker;
/// <summary>
/// �ړ������]�̂�����
/// </summary>
class MoveSaw :
    public Saw
{
public:
    /// <summary>
    /// �ړ������]�̂�����
    /// </summary>
    MoveSaw(PlacementData editData);
    /// <summary>
    /// �ړ����Ȃ����]����
    /// </summary>
    void Update()override;
private:
    enum class MoveParametor
    {
        //�ړ����x
        moveSpeed ,
        //�ړ�����
        moveTime
    };
    //�ړ�����
    ReusableTimer* moveLarpTimer;   
};

