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
    resultInfo.pos = hitCheckInfo.pos;
    resultInfo.hit = HitSituation::NotHit;
    //速さを足した場合のポジション
    VECTOR nextPos = VAdd(hitCheckInfo.pos, hitCheckInfo.velocity);
    VECTOR touchPos = nextPos;
    VECTOR lineVec = nextPos;
    bool isEndProcess = false;
    while (!isEndProcess)
    {
        isEndProcess = true;
        //範囲外に出ようとしているなら当たっている
        if (nextPos.x - hitCheckInfo.radius < firstPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            lineVec = VNorm(VCross(firstPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.z - firstPos.z);
            VECTOR OB = VSub(nextPos, firstPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//二つのオブジェクトの距離の向き
            //吹っ飛ぶ方向
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //吹っ飛んだ位置
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.x + hitCheckInfo.radius > endPos.x)
        {
            resultInfo.hit = HitSituation::Enter;
            lineVec = VNorm(VCross(endPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.z - firstPos.z);

            VECTOR OB = VSub(nextPos, endPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//二つのオブジェクトの距離の向き
            //吹っ飛ぶ方向
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //吹っ飛んだ位置
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.z - hitCheckInfo.radius < firstPos.z)
        {
            resultInfo.hit = HitSituation::Enter;

            lineVec = VNorm(VCross(firstPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.x - firstPos.x);

            VECTOR OB = VSub(nextPos, firstPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//二つのオブジェクトの距離の向き
            //吹っ飛ぶ方向
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //吹っ飛んだ位置
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        else if (nextPos.z + hitCheckInfo.radius > endPos.z)
        {
            resultInfo.hit = HitSituation::Enter;

            lineVec = VNorm(VCross(endPos, VGet(0, -1, 0)));
            lineVec = VScale(lineVec, endPos.x - firstPos.x);

            VECTOR OB = VSub(nextPos, endPos);
            float hValue = fabsf(VDot(OB, lineVec)) / VSize(lineVec);
            touchPos = VScale(VNorm(lineVec), hValue);

            VECTOR betweenDir = VNorm(VSub(touchPos, hitCheckInfo.pos));//二つのオブジェクトの距離の向き
            //吹っ飛ぶ方向
            resultInfo.bounceVec = VSub(hitCheckInfo.velocity, VScale(betweenDir, VDot(hitCheckInfo.velocity, betweenDir) * 2));
            //吹っ飛んだ位置
            resultInfo.pos = VAdd(resultInfo.pos, resultInfo.bounceVec);
            resultInfo.pos = touchPos;
            isEndProcess = false;
        }
        nextPos = resultInfo.pos;
    }
    return resultInfo;
}
