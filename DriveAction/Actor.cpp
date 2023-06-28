#include "Object.h"
#include "Actor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
Actor::Actor()

    :modelHandle(-1),
    velocity({})
{
}

Actor::Actor(ObjectInit::InitObjKind kind)
{
    objState = sleep;
    InitParamater(kind);
};
/// <summary>
/// 描画
/// </summary>
void Actor::Draw() const
{
    //描画するモデルがないなら終了
    if (modelHandle == -1)return;
    //変更前の行列を保存
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    //向きを変える
    ModelSetMatrix();
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, position);
    //サイズ変更
    MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
    MV1DrawModel(modelHandle);
    //行列を元に戻す
    MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// 速度所得
// </summary>
/// <returns></returns>
VECTOR Actor::GetVelocity()
{

    return velocity;

}
/// <summary>
/// 当たり判定で当たってたら渡す情報
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
/// <summary>
/// 他のオブジェクトに当たってるか調べる用の情報
/// </summary>
/// <returns></returns>
ArgumentConflictResultInfo Actor::GetConflictArgumentInfo()
{
    ArgumentConflictResultInfo resultInfo;
    resultInfo.SetObjInfo(this);
    return resultInfo;
}
/// <summary>
/// 描画モデルの行列をセット
/// </summary>
void Actor::ModelSetMatrix() const
{
    // 向きに合わせて回転.
    MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // モデルに向いてほしい方向に回転.
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// コンストラクタで呼ばれる処理
/// </summary>
void Actor::InitParamater(ObjectInit::InitObjKind kind)
{
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    //アセットを持ってくる
    modelHandle = initParam.modelHandle;
    //ポジション
    position = {};
    position.y = initParam.firstPosY;
    //向き
    direction = { 1,0,0 };
    //跳ね返り力
    bouncePower = initParam.setBouncePow;
    //半径
    radius = initParam.setRadius;
    //modelの大きさ
    modelSize = initParam.setModelSize;
}
/// <summary>
/// 位置や向きをVelocityに合わせて更新する
/// </summary>
void Actor::ReflectsVelocity()
{
    // 力をかけ終わったベロシティの方向にディレクションを調整.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // ポジションを更新.
    position = VAdd(position, velocity);
}
