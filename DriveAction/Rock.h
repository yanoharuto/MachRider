#pragma once
#include "SphereCollider.h"
#include "Actor.h"
#include "InitObjKind.h"
#include <string>
//��̃p�^�[���@�傫���Ƃ����ς��
#define RockPattern 3
/// <summary>
/// ��
/// </summary>
class Rock :
    public Actor
{
public:
    /// <summary>
    /// ��@3�p�^�[���̊₪����
    /// </summary>
    /// <param name="setPos"></param>
    /// <param name="pattern"></param>
    Rock(VECTOR setPos,int pattern);
    /// <summary>
    /// �����蔻�������
    /// </summary>
    ~Rock();
private:
    //�������蔻��
    SphereCollider* collider;
    static ObjectInit::InitObjKind rockPattern[RockPattern];
};

