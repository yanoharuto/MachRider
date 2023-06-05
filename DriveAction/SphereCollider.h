#pragma once
#include "conflictProccesor.h"

class SphereCollider final:
    public ConflictProccesor
{
public:
    SphereCollider(Actor* obj);
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo)override;
};

