#include <math.h>
#include "DxLib.h"
#include "StageObjectController.h"
#include "AssetManager.h"
#include "Utility.h"
#include "FirstPositionGetter.h"
#include "InitActor.h"
#include "Rock.h"
#include "StageWall.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
StageObjectController::StageObjectController(FirstPositionGetter* firstPosGetter)
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
    ////岩を配置する
    //auto rocksFirstPos = firstPosGetter->GetFirstPositionLoad(FirstPositionDataKind::rockPosition);
    //for (int i = 0; i < rocksFirstPos.size(); i++)
    //{
    //    for (int j = 0; j < rocksFirstPos[i].size(); j++)
    //    {
    //        actorList .push_back(new Rock(rocksFirstPos[i][j], i));
    //    }
    //}
    actorList.push_back(new StageWall());
}

/// <summary>
/// 岩削除
/// </summary>
/// <returns></returns>
StageObjectController::~StageObjectController()
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    
}


/// <summary>
/// コースのモデルを描画
/// </summary>
void StageObjectController::Draw() const
{
    for (auto ite = actorList.begin(); ite != actorList.end(); ite++)
    {
        (*ite)->Draw();
    }
    
    MV1DrawModel(floorModelHandle);
    //ライトの影響なしで空を描画
    SetUseLighting(false);
    MV1DrawModel(skyDomeModelHandle);
    
    SetUseLighting(true);
}