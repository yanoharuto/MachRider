#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// ���̓����蔻��
/// </summary>
class SphereCollider final:
    public SphereHitChecker
{
public:
    /// <summary>
/// ���̓����蔻��
/// </summary>
    SphereCollider(Actor* obj);
    /// <summary>
    /// ������ԕ����Ƃ���Ԃ�
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};