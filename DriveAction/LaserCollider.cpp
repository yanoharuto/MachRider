#include "LaserCollider.h"
#include "Actor.h"
LaserCollider::LaserCollider(Actor* obj, float setLineRange)
    :SphereHitChecker(obj)
{
    lineRange = setLineRange;
}
/// <summary>
/// Y���W�𖳎����Ă��邯�ǐ����̓����蔻��
/// </summary>
/// <param name="hitCheckInfo">�������Ă���z�̏��</param>
/// <returns></returns>
ConflictExamineResultInfo LaserCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    //���[�U�[�̏��
    HitCheckExamineObjectInfo lineInfo;
    lineInfo.SetExamineInfo(object);
    //object�̍������L�΂�
    float range = (object->GetPos().y - hitCheckInfo.pos.y) * lineRange;
    lineInfo.pos = VAdd(lineInfo.pos, VScale(object->GetDir(),  range));
    //�������Ă���z�̍����ɍ��킹��
    lineInfo.pos.y = hitCheckInfo.pos.y;

    if (SphereHitChecker::HitCheck(lineInfo, hitCheckInfo))
    {
        resultInfo.bounceVec = VSub(hitCheckInfo.pos, lineInfo.pos);
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        resultInfo.tag = object->GetTag();
        resultInfo.hit = HitSituation::Enter;
    }
    return resultInfo;
}