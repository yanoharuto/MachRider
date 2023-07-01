#include "WallCollider.h"
/// <summary>
/// �X�e�[�W�̊O�ɏo�Ȃ��悤�ɂ����
/// </summary>
/// <param name="owner"></param>
/// <param name="setFirstPos">����ȏ�̒l�ɂȂ����璵�˕Ԃ�</param>
/// <param name="setEndPos">����ȉ��̒l�ɂȂ����璵�˕Ԃ�</param>
WallCollider::WallCollider(Actor* owner,VECTOR setFirstPos, VECTOR setEndPos)
    :ConflictProccesor(owner)
{
    firstPos = setFirstPos;
    endPos = setEndPos;
}

WallCollider::~WallCollider()
{
}
/// <summary>
/// �������������ׂ�
/// </summary>
/// <param name="hitCheckInfo"></param>
/// <returns></returns>
ConflictExamineResultInfo WallCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo;//�Ԃ�l
    resultInfo.SetObjInfo(object);
    resultInfo.hit = HitSituation::NotHit;
    //�����𑫂����ꍇ�̃|�W�V����
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);

    //�͈͊O�ɏo�悤�Ƃ��Ă���Ȃ瓖�����Ă���
    if (nextPos.x < firstPos.x || nextPos.x > endPos.x)
    {
        resultInfo.hit = HitSituation::Enter;
    }
    else if(nextPos.z < firstPos.z || nextPos.z > endPos.z)
    {
        resultInfo.hit = HitSituation::Enter;
    }
    //�Ԃ����Ă���͂���
    if (resultInfo.hit == HitSituation::Enter)
    {
        resultInfo.bounceVec = VNorm(VScale(nextPos, -1));
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
    }

    return resultInfo;
}
