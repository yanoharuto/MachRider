#pragma once
#include "conflictProccesor.h"
/// <summary>
/// ‹…‘Ì“–‚½‚è”»’è
/// </summary>
class SphereCollider final:
    public ConflictProccesor
{
public:
    SphereCollider(Actor* obj);
    /// <summary>
    /// ‚Á”ò‚Ô•ûŒü‚Æ‚©‚ğ•Ô‚·
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};

