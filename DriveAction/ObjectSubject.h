#pragma once
#include "DxLib.h"
#include "Object.h"
class ConflictProccesor;

/// <summary>
/// �ώ@�Ώ� Observer�ɏ�񂪓���悤�ɂ���
/// </summary>
class ObjectSubject
{
public:
    /// <summary>
    /// �ώ@�Ώ� Observer�ɏ�񂪓���悤�ɂ���
    /// </summary>
    ObjectSubject(Object* setObj);
    ObjectSubject(Object* setObj, ConflictProccesor* setConProccesor);
    ~ObjectSubject();
    /// <summary>
    /// �I�u�W�F�N�g�̏ꏊ
    /// </summary>
    /// <returns></returns>
    VECTOR GetObjPos();
    /// <summary>
    /// �I�u�W�F�N�g�̌���
    /// </summary>
    /// <returns></returns>
    VECTOR GetObjDir();
    /// <summary>
    /// �I�u�W�F�N�g�̎��
    /// </summary>
    /// <returns></returns>
    Object::ObjectTag GetObjTag();
    /// <summary>
    /// �����̃^�O�̃I�u�W�F�N�g�ɉ���Ԃ�������
    /// </summary>
    /// <returns></returns>
    int GetTagObjectHitCount(Object::ObjectTag hitObjTag);
private:
    //�ώ@�Ώۂ̃I�u�W�F�N�g
    Object* subObject;
    //subObject�̓����蔻��
    ConflictProccesor* subCollider;
};