#include "SphereCollider.h"
#include "HitChecker.h"
#include "ConflictManager.h"

SphereCollider::SphereCollider(Actor* obj)
    :ConflictProccesor(obj)
{
}
/// <summary>
/// ������ԕ����Ƃ���Ԃ�
/// </summary>
/// <param name="hitCheckInfo">�������Ă������̏��</param>
/// <returns></returns>
ConflictExamineResultInfo SphereCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    //�������Ă��琁����ԕ����Ƃ���Ԃ�
    if (HitChecker::HitCheck(object, hitCheckInfo))
    {
        VECTOR betweenDir = VNorm(VSub(object->GetPos(), hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
        resultInfo.bounceVec = VSub(hitCheckInfo.velocity ,VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
        resultInfo.pos = VAdd(hitCheckInfo.pos,resultInfo.bounceVec);
        resultInfo.hit = HitSituation::Enter;
        resultInfo.SetObjInfo(object);
    }
    return resultInfo;
}
