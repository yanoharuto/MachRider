#pragma once
#include "DxLib.h"
#include "Object.h"
struct ArgumentConflictResultInfo
{
    Object::ObjectTag tag = Object::ObjectTag::obstacle;//�I�u�W�F�N�g�̃^�O
    VECTOR pos = {};
    VECTOR bounceVec = {};
    float radius = 0;//���a
    /// <summary>
    /// �����̃I�u�W�F�N�g��������쐬
    /// </summary>
    /// <param name="hit">�����蔻��œ���������</param>
    /// <param name="obj">��肽�����̃I�u�W�F�N�g</param>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        radius = obj->GetRadius();
    }
};