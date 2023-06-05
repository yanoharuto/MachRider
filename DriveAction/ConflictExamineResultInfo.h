#pragma once
#include "DxLib.h"
#include "Object.h"

enum class HitSituation
{
    NotHit,
    Enter,
    Stay,
    Exist
};
/// <summary>
/// �����蔻��̌��ʂŏo������
/// </summary>
struct ConflictExamineResultInfo
{
    HitSituation hit = HitSituation::NotHit;//�����蔻��œ���������
    Object::Object::ObjectTag tag = Object::ObjectTag::obstacle;//�I�u�W�F�N�g�̃^�O
    VECTOR bounceVec = {};
    VECTOR pos = {};
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
