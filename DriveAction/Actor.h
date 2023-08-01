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
    virtual void ConflictProcess(const ConflictExamineResultInfo conflictInfo) {};

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
};