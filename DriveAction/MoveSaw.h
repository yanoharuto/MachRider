#pragma once
#include "Saw.h"

class ReusableTimer;
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
    //最初の向き
    VECTOR firstDir;
    //移動時間
    ReusableTimer* moveLarpTimer;   
    //移動速度
    int speed = 0;
    
};

