#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
float StageWall::stageLength;
float StageWall::stageWidth;
/// <summary>
/// 行動範囲を狭める壁
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::wall)
{
    tag = ObjectTag::obstacle;
    position = setFirstPos;
    MV1SetPosition(modelHandle, VGet(0, 0, 0));
    wallCollider = new WallCollider(this, stageSmallestSize, stageBiggestSize);
    stageLength = fabsf(stageSmallestSize.z) + fabsf(stageBiggestSize.z);
    stageWidth = fabsf(stageSmallestSize.x) + fabsf(stageBiggestSize.x);
}

StageWall::~StageWall()
{
    ConflictManager::EraceConflictObjInfo(wallCollider);
}

/// <summary>
/// ステージの横幅
/// </summary>
/// <returns></returns>
float StageWall::GetStageWidth()
{
    return stageWidth;
}
/// <summary>
/// ステージの縦幅
/// </summary>
/// <returns></returns>
float StageWall::GetStageLength()
{
    return stageLength;
}