#include "LineCollider.h"
#include "HitChecker.h"
LineCollider::LineCollider(Actor* obj, float setLineRange)
    :ConflictProccesor(obj)
{
    lineRange = setLineRange;
}
/// <summary>
/// YÀ•W‚ğ–³‹‚µ‚Ä‚¢‚é‚¯‚Çü•ª‚Ì“–‚½‚è”»’è
/// </summary>
/// <param name="hitCheckInfo">“–‚½‚Á‚Ä‚­‚é“z‚Ìî•ñ</param>
/// <returns></returns>
ConflictExamineResultInfo LineCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    HitCheckExamineObjectInfo lineInfo;
    lineInfo.SetExamineInfo(object);
    //object‚Ì‚‚³•ªL‚Î‚·
    float range = (object->GetPos().y - hitCheckInfo.pos.y) * lineRange;
    lineInfo.pos = VAdd(lineInfo.pos, VScale(object->GetDir(),  range));
    //“–‚½‚Á‚Ä‚­‚é“z‚Ì‚‚³‚É‡‚í‚¹‚é
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
