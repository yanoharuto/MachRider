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
/// <param name="resultInfo">衝突時の結果</param>
void ConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //当たった時の処理を行う
        object->OnConflict(resultInfo);
    }
}
/// <summary>
/// 当たり判定で衝突しているか調べるのに必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
