#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"

/// <summary>
/// �������
/// </summary>
class Actor abstract:
    public Object
{
public:
    Actor(ObjectInit::InitObjKind kind);
    

    virtual ~Actor()
    {
    };

    /// <summary>
    /// �Փˏ���
    /// </summary>
    virtual void OnConflict(const CollisionResultInfo conflictInfo) {};

    /// <summary>
    /// �����蔻��œ������Ă���n�����
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitCheckExamineInfo();
    /// <summary>
    ///�@�Q�[���J�n���������B�I�[�o�[���C�h���Ȃ���Ε��ʂ̍X�V
    /// </summary>
    virtual void PrepareGame();
protected:
};