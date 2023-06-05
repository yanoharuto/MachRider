#pragma once
#include "SphereCollider.h"
#include "Actor.h"
#include "InitObjKind.h"
#include <string>
//岩のパターン　大きさとかが変わる
#define RockPattern 3
/// <summary>
/// 岩
/// </summary>
class Rock :
    public Actor
{
public:
    /// <summary>
    /// 岩　3パターンの岩がある
    /// </summary>
    /// <param name="setPos"></param>
    /// <param name="pattern"></param>
    Rock(VECTOR setPos,int pattern);
    /// <summary>
    /// 当たり判定を消す
    /// </summary>
    ~Rock();
private:
    //球当たり判定
    SphereCollider* collider;
    static ObjectInit::InitObjKind rockPattern[RockPattern];
};

