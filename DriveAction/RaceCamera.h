#pragma once
#include <iostream>
#include <memory>
#include "Camera.h"
class ObjectObserver;
/// <summary>
/// 遊んでいるときのカメラ
/// </summary>
class RaceCamera final : Camera
{
public:
    /// <summary>
    /// 遊んでいるときのカメラの初期化
    /// </summary>
    /// <param name="player">プレイヤーの位置</param>
    RaceCamera(std::weak_ptr<ObjectObserver> player);
    /// <summary>
    /// 位置や向きの更新
    /// </summary>
    void Update();
};

