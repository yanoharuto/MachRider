#pragma once
#include <string>
#include "UIManager.h"
#define TIMER_FONT_NUM 10


/// <summary>
/// 数字を描画する　横書き
/// </summary>
class NumUI
{
public:
    NumUI(UIKind kind);
    ~NumUI();
    /// <summary>
    /// 整数の描画
    /// </summary>
    /// <param name="num"></param>
    virtual void Draw(int num)const;
    /// <summary>
    /// 小数の描画　小数点付き
    /// </summary>
    /// <param name="num"></param>
    void Draw(float num) const;
    /// <summary>
    /// 中心座標X
    /// </summary>
    /// <returns></returns>
    int GetX()const { return numData.x; };
    /// <summary>
    /// 中心座標Y
    /// </summary>
    /// <returns></returns>
    int GetY()const { return numData.y; };
    /// <summary>
    /// 一文字の大きさ
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
protected:
    /// <summary>
    /// 数字の描画
    /// </summary>
    /// <param name="x">一番右端</param>
    /// <param name="y">Y座標</param>
    /// <param name="num">数字</param>
    /// <param name="scale">文字の大きさ</param>
    /// <returns>左端の座標</returns>
    int Draw(UIData data, int num)const;
    //数字のデータ
    UIData numData;
    //小数点の画像
    UIData pointData;
};