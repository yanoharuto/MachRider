#pragma once
#include "Camera.h"
/// <summary>
/// 編集モード時のカメラ
/// </summary>
class EditorCamera : public Camera
{
public:
    /// <summary>
    /// 編集モード時のカメラ
    /// </summary>
    EditorCamera();
    /// <summary>
    /// 上下キーで動かすことが出来る
    /// </summary>
    void Update();
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>カメラの向きベクトル</returns>
    static VECTOR GetNormDirection();
private:
    //回転速度
    const float rotaSpeed = 3.0f;
    //共有する向き
    static VECTOR staticDir;
};

