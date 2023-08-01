#pragma once
#include "Saw.h"

class ReusableTimer;
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
    MoveSaw(EditArrangementData editData);
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
    //�ŏ��̌���
    VECTOR firstDir;
    //�ړ�����
    ReusableTimer* moveLarpTimer;   
    //�ړ����x
    int speed = 0;
    
};

