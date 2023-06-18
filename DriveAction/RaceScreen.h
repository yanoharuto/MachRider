#pragma once
#include "DxLib.h"

/// <summary>
/// •`‰æ‚µ‚½‰æ‘œ‚ğ•Û‘¶‚·‚é
/// </summary>
class RaceScreen
{
public:
    RaceScreen();
    ~RaceScreen();
    /// <summary>
    /// •`‰æ‚µ‚Ä‚¢‚é‰æ‘œ‚ğXV
    /// </summary>
    void ScreenUpdate();
    void Draw();
    
private:
   int screen;
};

