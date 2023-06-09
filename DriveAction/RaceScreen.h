#pragma once
#include "DxLib.h"

/// <summary>
/// 描画した画像を保存する
/// </summary>
class RaceScreen
{
public:
    RaceScreen();
    ~RaceScreen();
    /// <summary>
    /// 描画した画面を保存
    /// </summary>
    void ScreenUpdate();
    /// <summary>
    /// 保存した画面を渡す
    /// </summary>
    /// <returns></returns>
    static int GetScreen();
    
private:
   static int screen;
};

