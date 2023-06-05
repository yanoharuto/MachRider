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
    ConflictExamineResultInfo resultInfo;
    resultInfo.SetObjInfo(object);
    resultInfo.hit = HitSituation::NotHit;
    VECTOR tempVec;
    if (hitCheckInfo.pos.x < firstPos.x || hitCheckInfo.pos.x > endPos.x)
    {
        resultInfo.hit = HitSituation::Enter;
        tempVec = VGet(0, 0, 1);
    }
    else if(hitCheckInfo.pos.z < firstPos.z || hitCheckInfo.pos.z > endPos.z)
    {
        resultInfo.hit = HitSituation::Enter;
        tempVec = VGet(1, 0, 0);
    }
    if (resultInfo.hit==HitSituation::Enter)
    {
        //�@������͂������傫�����o��
        float a = -VDot(VNorm(hitCheckInfo.velocity), tempVec);
        //�͂������x�N�g��
        tempVec = VSub(hitCheckInfo.velocity, VScale(tempVec, 2 * a));
        //�͂������̃|�W�V����
        resultInfo.pos = VAdd(hitCheckInfo.pos, tempVec);
        resultInfo.bounceVec = VScale(VNorm(hitCheckInfo.pos), - object->GetBouncePower());
    }

    return resultInfo;
}
