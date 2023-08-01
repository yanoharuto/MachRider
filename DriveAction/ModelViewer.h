#pragma once
#include "InitObjKind.h"
class Object;
/// <summary>
/// model�̕`��������
/// </summary>
class ModelViewer
{
public:
    /// <summary>
    /// model�̕`��������
    /// </summary>
    ModelViewer(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="drawObj">�ʒu�Ƃ��傫���Ƃ������Ă����炤</param>
    virtual void Draw(Object* drawObj) const;
protected:
    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    virtual void ModelSetMatrix(Object* drawObj) const;
    //�`�惂�f��
    int modelHandle;
};