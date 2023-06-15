#pragma once
#include <iostream>
#include <memory>
#include "DxLib.h"

class ObjectObserver;

/// <summary>
/// 影を描画するクラス
/// </summary>
class ShadowMap
{
public:
    /// <summary>
    /// 影を描画するクラス
    /// </summary>
    ShadowMap(std::shared_ptr<ObjectObserver> player);
    ~ShadowMap();
    /// <summary>
    /// 影の描画範囲の変更
    /// </summary>
    /// <param name="objInfo">引数の座標を中心にする</param>
    void SetShadowMapErea();
    /// <summary>
    /// これから描画する影の準備
    /// </summary>
    void SetUP();
    /// <summary>
    /// 影を描画するの終了
    /// </summary>
    void DrawEnd();
    /// <summary>
    /// 書き込んだシャドウマップを使う
    /// </summary>
    void Use();
private:
    //シャドウマップの最小範囲を設定
    VECTOR DrawAreaMinPos = VGet(-300.0f, -1.0f, -300.0f);
    //シャドウマップの最大範囲を設定
    VECTOR DrawAreaMaxPos = VGet(300.0f, 700.0f, 300.0f);
    //シャドウマップ作製
    int shadowMap = MakeShadowMap(2048, 2048);
    //こいつを軸に影を作る範囲を決める
     std::weak_ptr<ObjectObserver> playerObserber;
};

