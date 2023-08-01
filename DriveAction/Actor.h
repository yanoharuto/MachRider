#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"


/// <summary>
/// “®‚­‚â‚Â
/// </summary>
class Actor abstract:
    public Object
{
public:
    Actor(ObjectInit::InitObjKind kind);
    

    virtual ~Actor()
    {
    };

    /// <summary>
    /// Õ“Ëˆ—
    /// </summary>
    virtual void ConflictProcess(const ConflictExamineResultInfo conflictInfo) {};

    /// <summary>
    /// “–‚½‚è”»’è‚Å“–‚½‚Á‚Ä‚½‚ç“n‚·î•ñ
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo();
    /// <summary>
    /// ƒQ[ƒ€‚ªn‚Ü‚é‘O‚É‚·‚é‚±‚Æ
    /// </summary>
    virtual void GameReserve() {};
protected:
};