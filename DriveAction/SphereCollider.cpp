#include "SphereCollider.h"
#include "ConflictManager.h"
#include "Actor.h"
#include "HitCheckExamineObjectInfo.h"

SphereCollider::SphereCollider(Actor* obj)
    :SphereHitChecker(obj)
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
    if (SphereHitChecker::HitCheck(object, hitCheckInfo))
    {
        VECTOR nBetweenDir = VNorm(VSub(object->GetPos(), hitCheckInfo.pos));//��̃I�u�W�F�N�g�̋����̌���
        //������ԕ���
        resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(nBetweenDir, VDot(hitCheckInfo.velocity, nBetweenDir) * 2));
        //������񂾈ʒu
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        //�����������ǂ���
        resultInfo.hit = HitSituation::Enter;
        //�c���ݒ�
        resultInfo.SetObjInfo(object);
        //�����蔻��ύX
        hitCheckInfo.pos = resultInfo.pos;
    }

    return resultInfo;
}
