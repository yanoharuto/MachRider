#pragma once
#include "UIManager.h"
#include <iostream>
#include <memory>
class PlayerObserver;
/// <summary>
/// 収集アイテムの方向を記すエフェクトを出す
/// </summary>
class CollectCompass
{
public:
    /// <summary>
    /// エフェクトの読みこみ
    /// </summary>
    /// <param name="player">プレイヤーの位置などを貰うことが出来るオブザーバー</param>
    CollectCompass(std::weak_ptr<PlayerObserver> player);
    /// <summary>
    /// エフェクト終了
    /// </summary>
    ~CollectCompass();
    /// <summary>
    /// エフェクトの位置と向きを設定
    /// </summary>
    void Update();
private:
    //プレイヤーの位置や向きを取ってくる
    std::weak_ptr<PlayerObserver> playerObserver;
    //エフェクトハンドル
    int compassEffect = -1;
    //エフェクトのY座標
    const float addYPos = 13;
};