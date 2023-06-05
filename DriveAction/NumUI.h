#pragma once
#include <string>
#include "UIManager.h"
#define TIMER_FONT_NUM 10


/// <summary>
/// 数字を描画する
/// </summary>
class NumUI
{
public:
    NumUI(UIKind kind);
    ~NumUI();
    void Draw(int num);

    void Draw(float num);
    /// <summary>
    /// 一文字の大きさ
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
private:
    /// <summary>
    /// 数字を描画したい時用
    /// </summary>
    /// <param name="x">一番右端</param>
    /// <param name="y">Y座標</param>
    /// <param name="num">数字</param>
    /// <param name="scale">文字の大きさ</param>
    /// <returns>左端の座標</returns>
    int Draw(int x, int y, int num);
    //数字のデータ
    UIData numData;
    //小数点の画像
    UIData pointData;
};