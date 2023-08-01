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

    /// <summary>
    /// ステージの横幅
    /// </summary>
    /// <returns></returns>
    static float GetStageWidth();
    /// <summary>
    /// ステージの縦幅
    /// </summary>
    /// <returns></returns>
    static float GetStageLength();
private:
    //付き飛ばす力
    const float setBouncePower = 50;
    //ちょっと埋まってるから上に行く
    VECTOR setFirstPos = { 0,0.0f,0 };
    //行動範囲
    WallCollider* wallCollider;
    //マップの端１
    const VECTOR stageBiggestSize = { 2850,0,3150 };
    //マップの端2
    const VECTOR stageSmallestSize = { -3150,0,-2850 } ;
    //ステージの縦幅
    static float stageLength;
    //ステージの横幅
    static float stageWidth;
};

