#pragma once
#include "DxLib.h"

/// <summary>
/// •`‰æ‚µ‚½‰æ‘œ‚ð•Û‘¶‚·‚é
/// </summary>
class RaceScreen
{
public:
    RaceScreen();
    ~RaceScreen();
    /// <summary>
    /// •`‰æ‚µ‚½‰æ–Ê‚ð•Û‘¶
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// •Û‘¶‚µ‚½‰æ–Ê‚ð“n‚·
    /// </summary>
    /// <returns></returns>
    static int GetScreen();
    
private:
   static int screen;
};

