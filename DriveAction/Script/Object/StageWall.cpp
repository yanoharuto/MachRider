#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
//ステージの縦幅
float StageWall::stageLength;
//ステージの横幅
float StageWall::stageWidth;
/// <summary>
/// 行動範囲を狭める壁
/// </summary>
StageWall::StageWall()
    :Actor(ObjectInit::wall)
{
    tag = ObjectTag::obstacle;
    position = setFirstPos;
    //当たり判定
    wallCollider = new WallCollider(this, stageSmallestSize, stageBiggestSize);
    ConflictManager::AddHitChecker(wallCollider);
    //ステージの縦幅
    stageLength = fabsf(stageSmallestSize.z) + fabsf(stageBiggestSize.z);
    //ステージの横幅
    stageWidth = fabsf(stageSmallestSize.x) + fabsf(stageBiggestSize.x);
}
/// <summary>
/// 当たり判定消失
/// </summary>
StageWall::~StageWall()
{
    ConflictManager::EraceHitChecker(wallCollider);
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