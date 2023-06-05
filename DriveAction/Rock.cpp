#include "Rock.h"
#include "AssetManager.h"
#include "ConflictManager.h"
ObjectInit::InitObjKind Rock::rockPattern[RockPattern] = { ObjectInit::littleRock,ObjectInit::middleRock,ObjectInit::bigRock };
/// <summary>
/// ä‚
/// </summary>
/// <param name="setPos"></param>
/// <param name="pattern"></param>
Rock::Rock(VECTOR setPos, int pattern)
    :Actor(rockPattern[pattern])
{
    setPos.y = position.y;
    position = setPos;
    collider = new SphereCollider(this);
    tag = ObjectTag::obstacle;
}
/// <summary>
/// ìñÇΩÇËîªíËÇè¡Ç∑
/// </summary>
Rock::~Rock()
{
    ConflictManager::EraceConflictObjInfo(collider);
}

