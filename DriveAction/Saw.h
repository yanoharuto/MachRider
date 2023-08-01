#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
using namespace ObjectInit;
class SphereCollider;
/// <summary>
/// 障害物　（丸のこ）
/// </summary>
class Saw :
    public Actor
{
public:
    /// <summary>
    /// 引数の場所に設置する
    /// </summary>
    /// <param name="arrangementData">編集データ</param>
    Saw(EditArrangementData arrangementData);
    /// <summary>
    /// 当たり判定消去
    /// </summary>
    ~Saw()override;
    /// <summary>
    /// 回転させる
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
protected:
    //回転量
    const float addRotate = 20.0f;
    //はじき返す力
    const float setBouncePower = 4.0f;
    //厚み
    const float thickness = 5.0f;
    //当たり判定
    SphereCollider* collider;
};