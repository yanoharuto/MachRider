#pragma once
#include "Actor.h"
#include "DxLib.h"
class SphereCollider;
/// <summary>
/// 障害物　（丸のこ）
/// </summary>
class Saw :
    public Actor
{
public:
    Saw();
    /// <summary>
    /// 引数の場所に設置する
    /// </summary>
    /// <param name="pos"></param>
    Saw(VECTOR pos);
    ~Saw()override;
    /// <summary>
    /// 回転させる
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
private:
    //回転量
    const float addRotate = 22.0f;
    //はじき返す力
    const float setBouncePower = 4.0f;
    //厚み
    const float thickness = 5.0f;
    SphereCollider* collider;
};