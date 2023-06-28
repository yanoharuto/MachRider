#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class ObjectObserver;
/// <summary>
/// 収集アイテムの方向を記すエフェクトを出す
/// </summary>
class CollectSign
{
public:

    CollectSign(std::weak_ptr<ObjectObserver> player);
    ~CollectSign();
    /// <summary>
    /// エフェクトの位置と向きを設定
    /// </summary>
    void Update();
private:
    //プレイヤーの位置や向きを取ってくる
    std::weak_ptr<ObjectObserver> playerObserver;
    //エフェクトを出す
    int signEffect;
};