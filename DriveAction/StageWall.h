#pragma once
#include "Actor.h"
#include "WallCollider.h"
#include <string>
/// <summary>
/// 行動範囲を狭める壁
/// </summary>
class StageWall:public Actor
{
public:
    /// <summary>
    /// 行動範囲を狭める壁
    /// </summary>
    StageWall();
    //当たり判定を消す
    ~StageWall();
private:
    //付き飛ばす力
    const float setBouncePower = 50;
    //ちょっと埋まってるから上に行く
    VECTOR setFirstPos = { 0,100.0f,0 };
    //行動範囲
    WallCollider* wallCollider;
    //マップの端１
    VECTOR stageBiggestSize = { -3200,0,-3200 };
    //マップの端2
    VECTOR stageSmallestSize = { 2600,0,2600 };
};

