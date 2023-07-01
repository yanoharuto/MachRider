#pragma once
#include "DxLib.h"
#include <string>
#include "Object.h"
class ObjectSubject;
class ObjectObserver
{
public:
    /// <summary>
    /// �Ď���
    /// </summary>
    /// <param name="setSubject"></param>
    ObjectObserver(ObjectSubject* setSubject);
    ~ObjectObserver();
    /// <summary>
    /// �Ď��Ώۂ̈ʒu��n��
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectPos() const;
    /// <summary>
    /// �Ď��Ώۂ̌���
    /// </summary>
    /// <returns></returns>
    VECTOR GetSubjectDir() const;
    /// <summary>
    /// �Ď��Ώۂ������̂��̂ɓ��������񐔂�Ԃ�
    /// </summary>
    /// <param name="objTag"></param>
    /// <returns></returns>
    int GetSubjectHitCount(Object::ObjectTag objTag)const;
    /// <summary>
    /// �Ď��Ώۂ̏��
    /// </summary>
    /// <returns></returns>
    Object::ObjectState GetSubjectState()const;
private:
    ObjectSubject* subject;
};

