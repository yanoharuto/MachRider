#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "InitObjKind.h"

/// <summary>
/// �`�悷��I�u�W�F�N�g
/// </summary>
class Actor abstract:
    public Object
{
public:
    Actor() ;
    Actor(ObjectInit::InitObjKind kind);
    virtual ~Actor()
    {
    };
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() {};
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() const;
    
    /// <summary>
    /// �Փˏ���
    /// </summary>
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    /// <summary>
    /// ���x����
    // </summary>
    /// <returns></returns>
    VECTOR GetVelocity();
    /// <summary>
    /// �����蔻��œ������Ă���n�����
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo();

protected:
    /// <summary>
    /// ���̃I�u�W�F�N�g�ɓ������Ă邩���ׂ�p�̏��
    /// </summary>
    /// <returns></returns>
    ArgumentConflictResultInfo GetConflictArgumentInfo();
    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    virtual void ModelSetMatrix() const;
    
    //�|�W�V�����̈ʒu�ɕύX����
    virtual void UpdatePosition();
    
    //�`�惂�f��
    int modelHandle;
    //���x
    VECTOR velocity;
    //model�̃T�C�Y
    float modelSize = 1;
};