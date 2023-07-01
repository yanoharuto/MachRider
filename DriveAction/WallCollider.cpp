#include "WallCollider.h"
/// <summary>
/// ステージの外に出ないようにする壁
/// </summary>
/// <param name="owner"></param>
/// <param name="setFirstPos">これ以上の値になったら跳ね返す</param>
/// <param name="setEndPos">これ以下の値になったら跳ね返す</param>
WallCollider::WallCollider(Actor* owner,VECTOR setFirstPos, VECTOR setEndPos)
    :ConflictProccesor(owner)
{
    firstPos = setFirstPos;
    endPos = setEndPos;
}

WallCollider::~WallCollider()
{
}
/// <summary>
/// 当たったか調べる
/// </summary>
/// <param name="hitCheckInfo"></param>
/// <returns></returns>
ConflictExamineResultInfo WallCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo;//返り値
    resultInfo.SetObjInfo(object);
    resultInfo.hit = HitSituation::NotHit;
    //速さを足した場合のポジション
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);

    //範囲外に出ようとしているなら当たっている
    if (nextPos.x < firstPos.x || nextPos.x > endPos.x)
    {
        resultInfo.hit = HitSituation::Enter;
    }
    else if(nextPos.z < firstPos.z || nextPos.z > endPos.z)
    {
        resultInfo.hit = HitSituation::Enter;
    }
    //ぶつかってたらはじく
    if (resultInfo.hit == HitSituation::Enter)
    {
        resultInfo.bounceVec = VNorm(VScale(nextPos, -1));
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
    }

    return resultInfo;
}
