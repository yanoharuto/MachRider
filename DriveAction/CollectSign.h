#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class PlayerObserver;
/// <summary>
/// 収集アイテムの方向を記すエフェクトを出す
/// </summary>
class CollectSign
{
public:

    CollectSign(std::weak_ptr<PlayerObserver> player);
    /// <summary>
    /// エフェクト終了
    /// </summary>
    ~CollectSign();
    /// <summary>
    /// エフェクトの位置と向きを設定
    /// </summary>
    void Update();
private:
    //プレイヤーの位置や向きを取ってくる
    std::weak_ptr<PlayerObserver> playerObserver;
    //エフェクトハンドル
    int signEffect = -1;
    //エフェクトのY座標
    const float addYPos = 13;
};