#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// �I�u�W�F�N�g�̊Ď���
/// </summary>
class ObjectObserver
{
public:
    /// <summary>
    /// �I�u�W�F�N�g�̊Ď���
    /// </summary>
    /// <param name="setSubject">�Ď��������I�u�W�F�N�g</param>
    ObjectObserver(Object* const setSubject);
    /// <summary>
    /// �Ď��Ώۂ̈ʒu��n��
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectPos() const;
    /// <summary>
    /// �Ď��Ώۂ̌���
    /// </summary>
    /// <returns></returns>
    virtual VECTOR GetSubjectDir() const;
    /// <summary>
    /// �Ď��Ώۂ̏��
    /// </summary>
    /// <returns></returns>
    virtual Object::ObjectState GetSubjectState()const;
protected:
    //�Ď����Ă��镨
    Object* subject;
};

