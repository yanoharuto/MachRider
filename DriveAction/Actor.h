#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "InitObjKind.h"

/// <summary>
/// �������
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
    /// <summary>
    /// �Q�[�����n�܂�O�ɂ��邱��
    /// </summary>
    virtual void GameReserve() {};
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
    /// <summary>
    /// �R���X�g���N�^�ŌĂ΂�鏈��
    /// </summary>
    virtual void InitParamater(ObjectInit::InitObjKind kind);
    /// <summary>
    /// �ʒu�������Velocity�ɍ��킹�čX�V����
    /// </summary>
    virtual void ReflectsVelocity();

    
    //�`�惂�f��
    int modelHandle;
    //���x
    VECTOR velocity;
    //model�̃T�C�Y
    float modelSize = 1;
};