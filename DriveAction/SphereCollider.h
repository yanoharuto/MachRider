#pragma once
#include "conflictProccesor.h"
/// <summary>
/// ���̓����蔻��
/// </summary>
class SphereCollider final:
    public ConflictProccesor
{
public:
    SphereCollider(Actor* obj);
    /// <summary>
    /// ������ԕ����Ƃ���Ԃ�
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};

