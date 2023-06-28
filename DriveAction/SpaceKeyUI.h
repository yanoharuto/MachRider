#pragma once

#include "UIManager.h"
/// <summary>
/// spaceKeyの催促
/// </summary>
class SpaceKeyUI
{
public:
    SpaceKeyUI(int setX,int setY);
    ~SpaceKeyUI();
    /// <summary>
    /// アルファ値の更新
    /// </summary>
    void Update();
    /// <summary>
    /// 徐々に薄くなったり濃くなったりしながら描画
    /// </summary>
    void Draw()const;
private:
    //スペースキーUI
    UIData pressKeyData;
    //アルファ値
    int aValue;
    //アルファ値の増加速度
    const int aSpeed = 10;
    //アルファ値の最低値
    const int lowtestAvalue = 60;
    //アルファ値を増やすかどうか
    bool isAValueIncrement = false;
};