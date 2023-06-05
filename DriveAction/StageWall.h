#pragma once
#include "Actor.h"
#include "WallCollider.h"
#include <string>
/// <summary>
/// �s���͈͂����߂��
/// </summary>
class StageWall:public Actor
{
public:
    /// <summary>
    /// �s���͈͂����߂��
    /// </summary>
    StageWall();
    //�����蔻�������
    ~StageWall();
private:
    //�t����΂���
    const float setBouncePower = 50;
    //������Ɩ��܂��Ă邩���ɍs��
    VECTOR setFirstPos = { 0,100.0f,0 };
    //�s���͈�
    WallCollider* wallCollider;
    //�}�b�v�̒[�P
    VECTOR stageBiggestSize = { -3200,0,-3200 };
    //�}�b�v�̒[2
    VECTOR stageSmallestSize = { 2600,0,2600 };
};

