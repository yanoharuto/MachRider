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
    /// 描画している画像を更新
    /// </summary>
    void ScreenUpdate();
    void Draw();
    
private:
   int screen;
};

