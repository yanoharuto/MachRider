#include "EditorDrawModel.h"
#include "OriginalMath.h"
#include "EditorObject.h"
#include "InitActor.h"
/// <summary>
/// 各編集オブジェクトの描画担当役
/// </summary>
EditorDrawModel::EditorDrawModel(ObjectInit::InitObjKind kind)
    :DrawModel(kind)
{
}
/// <summary>
/// 引数の場所に描画
/// </summary>
/// <param name="data"></param>
void EditorDrawModel::Draw(PlacementData data) const
{
    //描画するモデルがないなら終了
    if (modelHandle == -1)return;
    //向きを変える
    ModelSetMatrix(VGet(data.dirX,0,data.dirZ));
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, VGet(data.posX,0,data.posZ));
    MV1DrawModel(modelHandle);
}
/// <summary>
/// 編集者が選択している物の表示　若干上に上がる
/// </summary>
/// <param name="data"></param>
void EditorDrawModel::SelectDraw(PlacementData data) const
{
    //描画するモデルがないなら終了
    if (modelHandle == -1)return;
    //向きを変える
    ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, VGet(data.posX, selectPosY, data.posZ));
    MV1DrawModel(modelHandle);
}
/// <summary>
/// 描画モデルの行列をセット
/// </summary>
/// <param name="dir"></param>
void EditorDrawModel::ModelSetMatrix(VECTOR dir) const
{
    // 向きに合わせて回転.
    MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // モデルに向いてほしい方向に回転.
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}