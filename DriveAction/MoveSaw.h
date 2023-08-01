#pragma once
#include "Saw.h"

class ReusableTimer;
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
    MoveSaw(EditArrangementData editData);
    /// <summary>
    /// ˆÚ“®‚µ‚È‚ª‚ç‰ñ“]‚·‚é
    /// </summary>
    void Update()override;
private:
    enum MoveParam
    {
        //ˆÚ“®‘¬“x
        moveSpeed = 1,
        //ˆÚ“®ŠÔ
        moveTime=3
    };
    //Å‰‚ÌŒü‚«
    VECTOR firstDir;
    //ˆÚ“®ŠÔ
    ReusableTimer* moveLarpTimer;   
    //ˆÚ“®‘¬“x
    int speed = 0;
    
};

