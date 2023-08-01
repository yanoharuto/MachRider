#pragma once
#include "Camera.h"
/// <summary>
/// 編集モード時のカメラ
/// </summary>
class EditorCamera :
    public Camera
{
public:
    EditorCamera();
    void Update();
    /// <summary>
    /// 向き
    /// </summary>
    /// <returns></returns>
    static VECTOR GetNormDirection();
private:
    const float rotaSpeed = 3.0f;
    static VECTOR staticDir;
};

