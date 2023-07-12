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
    /// <summary>
    /// �ǂ̕`��
    /// </summary>
    void Draw()const override;
private:
    //�t����΂���
    const float setBouncePower = 50;
    //������Ɩ��܂��Ă邩���ɍs��
    VECTOR setFirstPos = { 0,100.0f,0 };
    //�s���͈�
    WallCollider* wallCollider;
    //�}�b�v�̒[�P
    VECTOR stageBiggestSize = { 2850,0,3150 };
    //�}�b�v�̒[2
    VECTOR stageSmallestSize = { -3150,0,-2850 } ;
};

