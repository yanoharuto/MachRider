#include "ModelViewer.h"
#include "DxLib.h"
#include "Object.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// modelの描画をする役
/// </summary>
ModelViewer::ModelViewer(ObjectInit::InitObjKind kind)
{
    modelHandle = InitActor::GetModelHandle(kind);
}

/// <summary>
/// modelの大きさに合わせて描画する
/// </summary>
/// <param name="drawObj">位置とか大きさとか教えてももらう</param>
void ModelViewer::Draw(Object* const drawObj) const
{
    //描画するモデルがないなら終了
    if (modelHandle == -1)return;
    MV1SetMatrix(modelHandle, MGetIdent());
    //向きを変える
    ModelSetMatrix(drawObj);
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, drawObj->GetPos());
    //描画
    MV1DrawModel(modelHandle);
}

/// <summary>
/// 描画モデルの行列をセット
/// </summary>
void ModelViewer::ModelSetMatrix(Object* const drawObj) const
{
    // 向きに合わせて回転.
    MV1SetRotationZYAxis(modelHandle, drawObj->GetDir(), VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // モデルに向いてほしい方向に回転.
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}