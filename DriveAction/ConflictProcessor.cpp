#include "ConflictProcessor.h"
#include "Actor.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
/// <summary>
/// 衝突処理実行役
/// </summary>
/// <param name="obj">実行したい衝突処理があるオブジェクト</param>
ConflictProcessor::ConflictProcessor(Actor* const obj)
{
    object = obj;
}

/// <summary>
/// 当たり判定の処理を呼び出す
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProcessor::ConflictProcess(ConflictExamineResultInfo resultInfo)
{
    //衝突後の処理を行う必要がないなら終了
    if (object == nullptr)return;

    if (resultInfo.hit != HitSituation::NotHit)
    {
        //当たった時の処理を行う
        object->ConflictProcess(resultInfo);
    }
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
