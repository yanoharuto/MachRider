#pragma once
#include "Saw.h"
#include "EditObjectData.h"
class ReusableTimer;
class SphereCollider;
/// <summary>
/// 移動する回転のこぎり
/// </summary>
class MoveSaw :
    public Saw
{
public:
    /// <summary>
/// 移動する回転のこぎり
/// </summary>
    MoveSaw(EditArrangementData editData);
    /// <summary>
    /// 移動しながら回転する
    /// </summary>
    void Update()override;
private:
    enum MoveParam
    {
        //移動速度
        moveSpeed = 1,
        //移動時間
        moveTime=3
    };
    //移動時間
    ReusableTimer* moveLarpTimer;   
};

