#include "MeshCollider.h"
#include "ConflictManager.h"
MeshCollider::MeshCollider(int setModelHandle, Object::ObjectTag setTag)
{
    modelHandle = setModelHandle;
    tag = setTag;
    ConflictManager::AddConflictObjInfo(this);
}

MeshCollider::~MeshCollider()
{
}
/// <summary>
/// 当たり判定を返す
/// </summary>
/// <param name=""></param>
/// <returns></returns>
ConflictExamineResultInfo MeshCollider::HitCheck(HitCheckExamineObjectInfo examinInfo)
{
    return GetSphereConflictModelInfo(examinInfo);
}


/// <summary>
/// MV1CollCheck_Sphereを使ってモデルハンドルが射程内か調べるよ
/// </summary>
/// <param name="modelHandle">調べるモデル</param>
/// <param name="examineInfo">調べるために必要な情報</param>
/// <returns>ぶつかった位置を返すよ。ぶつかってないならHitFlagはfalse</returns>
ConflictExamineResultInfo MeshCollider::GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo) 
{
    DxLib::MV1_COLL_RESULT_POLY_DIM polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, examineInfo.pos, examineInfo.radius);
    //はじかれ先のポジション
    VECTOR bounceVec = {};
    //はじかれ先のポジション
    VECTOR nowPos = examineInfo.pos;
    bool hitFlag = false;
    //当たったかどうか
    ConflictExamineResultInfo resultInfo;
    resultInfo.tag = tag;
    //modelにぶつかっているか
    if (polyDimInfo.HitNum != 0)
    {
        hitFlag = true;
        //当たらない位置に移動するまで処理
        while (hitFlag && fabsf(VSize(examineInfo.velocity)) > 0)
        {
            //ポリゴンの数だけ吹き飛ばす
            for (int i = 0; i < polyDimInfo.HitNum; i++)
            {
                MV1_COLL_RESULT_POLY polyInfo = polyDimInfo.Dim[i];//ポリゴンの頂点情報
                float a = -VDot(VNorm(examineInfo.velocity), polyInfo.Normal);//法線からはじかれる大きさを出す
                //はじかれるベクトル
                bounceVec = VSub(examineInfo.velocity, VScale(polyInfo.Normal, 2 * a));
                //はじかれ先のポジション
                nowPos = VAdd(nowPos, bounceVec);
            }
            MV1CollResultPolyDimTerminate(polyDimInfo);//一度ポリゴン情報を消す
            //もう一度当たっている部分があるか調べる
            polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, nowPos, examineInfo.radius);
            //何も当たってなかったら終了
            hitFlag = polyDimInfo.HitNum != 0;
        }
        //最終的にBouncePower分吹き飛ばす
        resultInfo.hit = HitSituation::Enter;
        resultInfo.bounceVec = VScale(VNorm(VSub(examineInfo.pos, nowPos)),20);
        resultInfo.pos = nowPos;
        //後処理
        MV1CollResultPolyDimTerminate(polyDimInfo);
        return  resultInfo;
    }
    //当たってない場合
    resultInfo.hit = HitSituation::NotHit;
    MV1CollResultPolyDimTerminate(polyDimInfo);
    return resultInfo;
}
/// <summary>
/// meshなので位置とかは教えれない
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo MeshCollider::GetHitExamineCheckInfo()
{
    return { {},{},0};
}
/// <summary>
/// 当たった場合の反応
/// </summary>
/// <param name="resultInfo"></param>
void MeshCollider::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
}