#pragma once
#include "ConflictProccesor.h"
/// <summary>
/// YÀ•W‚ğ–³‹‚µ‚Ä‚¢‚é‚¯‚Çü•ª‚Ì“–‚½‚è”»’è
/// </summary>
class LineCollider :
    public ConflictProccesor
{
public:
    //ü•ª‚Ì’·‚³‚Í‚‚³‚ÆŒW”‚É‚æ‚Á‚ÄŒˆ‚ß‚é
    LineCollider(Actor* obj,float setLineRange);

    /// <summary>
    /// YÀ•W‚ğ–³‹‚µ‚Ä‚¢‚é‚¯‚Çü•ª‚Ì“–‚½‚è”»’è
    /// </summary>
    /// <param name="hitCheckInfo">“–‚½‚Á‚Ä‚­‚é“z‚Ìî•ñ</param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
private:
    //ü•ª‚Ì’·‚³‚Í‚‚³‚ÆŒW”‚É‚æ‚Á‚ÄŒˆ‚ß‚é
    float lineRange;
};

