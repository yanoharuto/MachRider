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
    resultInfo.pos = hitCheckInfo.pos;
    resultInfo.hit = HitSituation::NotHit;
    //�����𑫂����ꍇ�̃|�W�V����
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);
    VECTOR touchPos = nextPos;
    VECTOR lineVec = nextPos;
    bool isEndProcess = false;
    while (!isEndProcess)
    {
        isEndProcess = true;
        //�͈͊O�ɏo�悤�Ƃ��Ă���Ȃ瓖�����Ă���
        if (nextPos.x - hitCheckInfo.radius < firstPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            lineVec = VNorm(VCross(firstPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.z - firstPos.z);
            VECTOR OB = VSub(nextPos, firstPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
            //������ԕ���
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //������񂾈ʒu
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.x + hitCheckInfo.radius > endPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            lineVec = VNorm(VCross(endPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.z - firstPos.z);

            VECTOR OB = VSub(nextPos, endPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
            //������ԕ���
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //������񂾈ʒu
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.z - hitCheckInfo.radius < firstPos.z)
        {
            resultInfo.hit = HitSituation::Enter;

            lineVec = VNorm(VCross(firstPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.x - firstPos.x);

            VECTOR OB = VSub(nextPos, firstPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
            //������ԕ���
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //������񂾈ʒu
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.z + hitCheckInfo.radius > endPos.z)
        {
            resultInfo.hit = HitSituation::Enter;

            lineVec = VNorm(VCross(endPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.x - firstPos.x);

            VECTOR OB = VSub(nextPos, endPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
            //������ԕ���
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //������񂾈ʒu
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        nextPos = resultInfo.pos;
    }
    return resultInfo;
}
