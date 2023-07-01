#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
/// <summary>
/// çsìÆîÕàÕÇã∑ÇﬂÇÈï«
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::wall)
{
    tag = ObjectTag::obstacle;
    position = setFirstPos;
    MV1SetPosition(modelHandle, VGet(0, 0, 0));
    MV1SetScale(modelHandle, VGet(modelSize,modelSize,modelSize));
    wallCollider = new WallCollider(this, stageBiggestSize, stageSmallestSize);
}

StageWall::~StageWall()
{
    ConflictManager::EraceConflictObjInfo(wallCollider);
}

void StageWall::Draw() const
{
    MV1DrawModel(modelHandle);
}