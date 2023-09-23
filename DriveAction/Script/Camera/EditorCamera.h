#pragma once
#include "Camera.h"
#include "EditObjectData.h"
/// <summary>
/// 編集モード時のカメラ
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// カメラのスピードなどの初期化
    /// </summary>
    EditorCamera();
    /// <summary>
    /// カメラの見るべき向きを変更
    /// </summary>
    /// <param name="targetPlaceData">向きたい場所の配置情報</param>
    void UpdatePositionAndTarget(PlacementData targetPlaceData);
    /// <summary>
    /// 上下左右キーで向きとターゲットまでの距離を変更する
    /// </summary>
    void UpdateDirectionAndTargetBetween();

private:
    //回転速度
    const float rotaSpeed = 3.0f;
};

