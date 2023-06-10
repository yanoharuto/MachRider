#include <math.h>
#include "CircuitTrack.h"
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
CircuitTrack::CircuitTrack(FirstPositionGetter* firstPosGetter)
{
    //地面の初期化
    auto initParam= InitActor::GetActorParamator(stageFloor);
    
    floorModelHandle = initParam.modelHandle;
    auto rocksFirstPos = firstPosGetter->GetFirstPositionLoad(FirstPositionDataKind::rockPosition);
    //岩を配置する
    for (int i = 0; i < rocksFirstPos.size(); i++)
    {
        for (int j = 0; j < rocksFirstPos[i].size(); j++)
        {
            Rock* rock = new Rock(rocksFirstPos[i][j], i);
            rocks.push_back(rock);
        }

    }
    stageWall = new StageWall();
}

/// <summary>
/// 岩削除
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    SAFE_DELETE(stageWall);
}


/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        (*ite)->Draw();
    }
    stageWall->Draw();
    MV1DrawModel(floorModelHandle);
}