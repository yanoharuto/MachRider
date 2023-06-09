#include "LineCollider.h"
#include "HitChecker.h"
LineCollider::LineCollider(Actor* obj, float setLineRange)
    :ConflictProccesor(obj)
{
    lineRange = setLineRange;
}
/// <summary>
/// Y座標を無視しているけど線分の当たり判定
/// </summary>
/// <param name="hitCheckInfo">当たってくる奴の情報</param>
/// <returns></returns>
ConflictExamineResultInfo LineCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    HitCheckExamineObjectInfo lineInfo;
    lineInfo.SetExamineInfo(object);
    //objectの高さ分伸ばす
    float range = (object->GetPos().y - hitCheckInfo.pos.y) * lineRange;
    lineInfo.pos = VAdd(lineInfo.pos, VScale(object->GetDir(),  range));
    //当たってくる奴の高さに合わせる
    lineInfo.pos.y = hitCheckInfo.pos.y;

    if (HitChecker::HitCheck(lineInfo, hitCheckInfo))
    {
        resultInfo.bounceVec = VSub(hitCheckInfo.pos, lineInfo.pos);
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        resultInfo.tag = object->GetTag();
        resultInfo.hit = HitSituation::Enter;
    }
    return resultInfo;
}
