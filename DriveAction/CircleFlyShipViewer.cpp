#include "CircleFlyShipViewer.h"
#include "CSVFileLoader.h"
#include "OriginalMath.h"
#include "DxLib.h"
#include "InitObjKind.h"
#include "FlyShipController.h"
#include "EditorModelViewer.h"
CircleFlyShipViewer::CircleFlyShipViewer()
    :EditorModelViewer(ObjectInit::circleLaserShip)
{
    Init();
}
/// <summary>
/// 普通に円を作っている機体を描画
/// </summary>
/// <param name="data"></param>
void CircleFlyShipViewer::Draw(EditArrangementData data) const
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
        //サイズ変更
        MV1SetScale(modelHandle, VGet(mSize, mSize, mSize));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// 若干上空に描画する
/// </summary>
/// <param name="data"></param>
void CircleFlyShipViewer::SelectDraw(EditArrangementData data) const
{
    VECTOR dataDir = VGet(data.dirX, 0, data.dirZ);
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
        //サイズ変更
        MV1SetScale(modelHandle, VGet(mSize, mSize, mSize));
        MV1DrawModel(modelHandle);
    }
}
/// <summary>
/// 円を作るために必要な情報を所得
/// </summary>
void CircleFlyShipViewer::Init()
{
    //配置に必要な情報
    using namespace FlyShipInit;
    //FlyShip用のデータをロード
    CSVFileLoader* addDataLoader = new CSVFileLoader(InitActor::GetActorParamator(circleLaserShip).addData);
    auto addData = addDataLoader->GetLoadCharData();
    uniNum = atof(addData[unitNum]);
    uniBetween = atof(addData[unitBetween]);
    //機体の数だけ割る
    
    uniDirRota = 360.0f / uniNum;
}
