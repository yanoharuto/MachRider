#pragma once
#include "ConflictProccesor.h"
/// <summary>
/// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
/// </summary>
class WallCollider :
    public ConflictProccesor
{
public:
    /// <summary>
    /// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
    /// </summary>
    /// <param name="owner"></param>
    /// <param name="setFirstPos">����ȏ�̒l�ɂȂ����璵�˕Ԃ�</param>
    /// <param name="setEndPos">����ȉ��̒l�ɂȂ����璵�˕Ԃ�</param>
    WallCollider(Actor* owner,VECTOR setFirstPos,VECTOR setEndPos);
    ~WallCollider();
    /// <summary>
    /// �������������ׂ�
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) override;
private:
    //����ȏ�̒l�ɂȂ����璵�˕Ԃ�
    VECTOR firstPos;
    //����ȉ��̒l�ɂȂ����璵�˕Ԃ�
    VECTOR endPos;
};

