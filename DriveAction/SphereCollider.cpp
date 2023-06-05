#include "SphereCollider.h"
#include "HitChecker.h"
#include "ConflictManager.h"

SphereCollider::SphereCollider(Actor* obj)
    :ConflictProccesor(obj)
{
}

ConflictExamineResultInfo SphereCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    if (HitChecker::HitCheck(object, hitCheckInfo))
    {
        resultInfo.bounceVec = VNorm(VSub(hitCheckInfo.pos, object->GetPos()));
        resultInfo.pos = VAdd(object->GetPos(), VScale(resultInfo.bounceVec, object->GetRadius() + object->GetBouncePower()));
        resultInfo.tag = object->GetTag();
        resultInfo.hit = HitSituation::Enter;
    }
    return resultInfo;
}
