#include <math.h>
#include "DxLib.h"
#include "StageObjectController.h"
#include "AssetManager.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "InitActor.h"
#include "StageWall.h"
#include "ModelViewer.h"
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController()
    :ActorController(ObjectInit::wall)
{   
    //床の設定
    auto param = InitActor::GetActorParamator(stageFloor);
    floorModelHandle = param.modelHandle;
    MV1SetScale(floorModelHandle, VGet(param.setModelSize, param.setModelSize, param.setModelSize));
    MV1SetPosition(floorModelHandle, VGet(0, param.firstPosY, 0));
    //skyDomeの設定
    param = InitActor::GetActorParamator(skyDome);
    skyDomeModelHandle = param.modelHandle;
    MV1SetScale(skyDomeModelHandle, VGet(param.setModelSize, param.setModelSize, param.setModelSize));
    stageWall = new StageWall();
    viewer = new ModelViewer(wall);
}

/// <summary>
/// 岩削除
/// </summary>
/// <returns></returns>
StageObjectController::~StageObjectController()
{
    SAFE_DELETE(stageWall);
    SAFE_DELETE(viewer);
}

/// <summary>
/// コースのモデルを描画
/// </summary>
void StageObjectController::Draw() const
{
    //壁と床
    viewer->Draw(stageWall);
    MV1DrawModel(floorModelHandle);
    //ライトの影響なしで空を描画
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    SetUseLighting(true);
}
/// <summary>
/// シーンが切り替えるまではずっといる
/// </summary>
/// <returns></returns>
bool StageObjectController::IsAlive() const
{
    return true;
}
