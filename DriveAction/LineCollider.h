#pragma once
#include "ConflictProccesor.h"
/// <summary>
/// Y���W�𖳎����Ă��邯�ǐ����̓����蔻��
/// </summary>
class LineCollider :
    public ConflictProccesor
{
public:
    //�����̒����͍����ƌW���ɂ���Č��߂�
    LineCollider(Actor* obj,float setLineRange);

    /// <summary>
    /// Y���W�𖳎����Ă��邯�ǐ����̓����蔻��
    /// </summary>
    /// <param name="hitCheckInfo">�������Ă���z�̏��</param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
private:
    //�����̒����͍����ƌW���ɂ���Č��߂�
    float lineRange;
};

