#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
/// <summary>
/// s“®”ÍˆÍ‚ğ‹·‚ß‚é•Ç
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::wall)
{
    tag = ObjectTag::stage;
    position = setFirstPos;
    wallCollider = new WallCollider(this, stageBiggestSize, stageSmallestSize);
}

StageWall::~StageWall()
{
    ConflictManager::EraceConflictObjInfo(wallCollider);
}
