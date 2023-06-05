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
    ConflictExamineResultInfo resultInfo;
    resultInfo.SetObjInfo(object);
    resultInfo.hit = HitSituation::NotHit;
    VECTOR tempVec;
    if (hitCheckInfo.pos.x < firstPos.x || hitCheckInfo.pos.x > endPos.x)
    {
        resultInfo.hit = HitSituation::Enter;
        tempVec = VGet(0, 0, 1);
    }
    else if(hitCheckInfo.pos.z < firstPos.z || hitCheckInfo.pos.z > endPos.z)
    {
        resultInfo.hit = HitSituation::Enter;
        tempVec = VGet(1, 0, 0);
    }
    if (resultInfo.hit==HitSituation::Enter)
    {
        //法線からはじかれる大きさを出す
        float a = -VDot(VNorm(hitCheckInfo.velocity), tempVec);
        //はじかれるベクトル
        tempVec = VSub(hitCheckInfo.velocity, VScale(tempVec, 2 * a));
        //はじかれ先のポジション
        resultInfo.pos = VAdd(hitCheckInfo.pos, tempVec);
        resultInfo.bounceVec = VScale(VNorm(hitCheckInfo.pos), - object->GetBouncePower());
    }

    return resultInfo;
}
