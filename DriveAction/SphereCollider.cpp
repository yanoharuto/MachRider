#include "SphereCollider.h"
#include "HitChecker.h"
#include "ConflictManager.h"

SphereCollider::SphereCollider(Actor* obj)
    :ConflictProccesor(obj)
{
}
/// <summary>
/// 吹っ飛ぶ方向とかを返す
/// </summary>
/// <param name="hitCheckInfo">当たってきた方の情報</param>
/// <returns></returns>
ConflictExamineResultInfo SphereCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    //当たってたら吹っ飛ぶ方向とかを返す
    if (HitChecker::HitCheck(object, hitCheckInfo))
    {
        VECTOR betweenDir = VNorm(VSub(object->GetPos(), hitCheckInfo.pos));//二つのオブジェクトの距離の向き
        //吹っ飛ぶ方向
        resultInfo.bounceVec = VSub(hitCheckInfo.velocity ,VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
        //吹っ飛んだ位置
        resultInfo.pos = VAdd(hitCheckInfo.pos,resultInfo.bounceVec);
        //当たったかどうか
        resultInfo.hit = HitSituation::Enter;
        //残りを設定
        resultInfo.SetObjInfo(object);
    }
    return resultInfo;
}
