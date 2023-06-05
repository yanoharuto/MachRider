#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// �����蔻��Ŏg�������ɂ��ēn���������
/// </summary>
struct HitCheckExamineObjectInfo
{
    VECTOR pos = {};//�|�W�V����
    VECTOR velocity = {};//�ړ���
    float radius = 0;//���a
    Object::ObjectTag tag;
    void SetExamineInfo(Object* obj)
    {
        tag = obj->GetTag();
        pos = obj->GetPos();
        radius = obj->GetRadius();
    }
};