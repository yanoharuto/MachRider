#pragma once
#include "Saw.h"
#include "EditObjectData.h"
class ReusableTimer;
class SphereHitChecker;
/// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è
/// </summary>
class MoveSaw :
    public Saw
{
public:
    /// <summary>
/// ˆÚ“®‚·‚é‰ñ“]‚Ì‚±‚¬‚è
/// </summary>
    MoveSaw(PlacementData editData);
    /// <summary>
    /// ˆÚ“®‚µ‚È‚ª‚ç‰ñ“]‚·‚é
    /// </summary>
    void Update()override;
private:
    enum MoveParam
    {
        //ˆÚ“®‘¬“x
        moveSpeed = 1,
        //ˆÚ“®ŽžŠÔ
        moveTime=3
    };
    //ˆÚ“®ŽžŠÔ
    ReusableTimer* moveLarpTimer;   
};

