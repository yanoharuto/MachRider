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
    enum MoveParam
    {
        //�ړ����x
        moveSpeed = 1,
        //�ړ�����
        moveTime=3
    };
    //�ړ�����
    ReusableTimer* moveLarpTimer;   
};

