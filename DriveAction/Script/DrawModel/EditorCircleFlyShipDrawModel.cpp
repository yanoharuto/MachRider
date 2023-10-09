#include "EditorCircleFlyShipDrawModel.h"
#include "CSVFileLoader.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "InitObjKind.h"
#include "FlyShipController.h"
#include "EditorDrawModel.h"
#include "Utility.h"
/// <summary>
/// 円形飛行艇は編集時は陣形の飛行機纏めて描画する
/// そのために必要な情報を初期化
/// </summary>
EditorCircleFlyShipDrawModel::EditorCircleFlyShipDrawModel()
    :EditorDrawModel(ObjectInit::InitObjKind::circleLaserShip)
{
    Init();
}
/// <summary>
/// 普通に円を作っている機体を描画
/// </summary>
/// <param name="data">配置位置</param>
void EditorCircleFlyShipDrawModel::Draw(PlacementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    VECTOR dataPos = VGet(data.posX, 0, data.posZ);
    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota)); 
        //描画するモデルがないなら終了
        if (modelHandle == -1)return;
        //向きを変える
        ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
        // ３Dモデルのポジション設定
        MV1SetPosition(modelHandle, VAdd(dataPos,VScale(dataDir,uniBetween)));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// 若干上空に描画する
/// </summary>
/// <param name="data">配置情報</param>
void EditorCircleFlyShipDrawModel::SelectDraw(PlacementData data) const
{
    //円の向き
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
    //円の中心
    VECTOR dataPos = VGet(data.posX, selectPosY, data.posZ);

    for (int i = 0; i < uniNum; i++)
    {
        dataDir = VNorm(OriginalMath::GetYRotateVector(dataDir, uniDirRota));
        //描画するモデルがないなら終了
        if (modelHandle == -1)return;
        //向きを変える
        ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
        // ３Dモデルのポジション設定
        MV1SetPosition(modelHandle, VAdd(dataPos, VScale(dataDir, uniBetween)));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// 円を作るために必要な情報を所得
/// </summary>
void EditorCircleFlyShipDrawModel::Init()
{
    //配置に必要な情報
    using enum FlyShipInit::FlyShipParamator;

    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(AddDataObject::circleFlyShip));
    auto addData = addDataLoader->GeFileStringData();
    uniNum = STR_TO_I(addData[CAST_I(unitNum)]);
    uniBetween = STR_TO_F(addData[CAST_I(unitBetween)]);
    //機体の数だけ割る
    uniDirRota = 360.0f / uniNum;
}
