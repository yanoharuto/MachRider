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
    /// �X�e�[�W�̉���
    /// </summary>
    /// <returns></returns>
    static float GetStageWidth();
    /// <summary>
    /// �X�e�[�W�̏c��
    /// </summary>
    /// <returns></returns>
    static float GetStageLength();
private:
    //�t����΂���
    const float setBouncePower = 50;
    //������Ɩ��܂��Ă邩���ɍs��
    VECTOR setFirstPos = { 0,0.0f,0 };
    //�s���͈�
    WallCollider* wallCollider;
    //�}�b�v�̒[�P
    const VECTOR stageBiggestSize = { 2850,0,3150 };
    //�}�b�v�̒[2
    const VECTOR stageSmallestSize = { -3150,0,-2850 } ;
    //�X�e�[�W�̏c��
    static float stageLength;
    //�X�e�[�W�̉���
    static float stageWidth;
};

