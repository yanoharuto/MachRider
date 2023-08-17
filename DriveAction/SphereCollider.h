#pragma once
#include "SphereHitChecker.h"
/// <summary>
/// ‹…‘Ì“–‚½‚è”»’è
/// </summary>
class SphereCollider final:
    public SphereHitChecker
{
public:
    /// <summary>
/// ‹…‘Ì“–‚½‚è”»’è
/// </summary>
    SphereCollider(Actor* obj);
    /// <summary>
    /// ‚Á”ò‚Ô•ûŒü‚Æ‚©‚ğ•Ô‚·
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};