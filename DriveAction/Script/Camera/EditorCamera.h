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
    /// 上下左右キーで動かすことが出来る
    /// </summary>
    /// <param name="targetPlaceData">向きたい場所の配置情報</param>
    void Update(PlacementData targetPlaceData);
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>カメラの向きベクトル</returns>
    VECTOR GetNormDirection();
private:
    //回転速度
    const float rotaSpeed = 3.0f;
};

