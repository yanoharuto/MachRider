#pragma once
#include <memory>
#include <iostream>
#include "DxLib.h"
class Object;
class Camera;
/// <summary>
/// カメラの向きをオブジェクトに渡すためのクラス
/// </summary>
class CameraObserver
{
public:
    /// <summary>
    /// カメラを共有してもらう
    /// </summary>
    /// <param name="setCamera">共有してもらうカメラ</param>
    CameraObserver(std::shared_ptr<Camera> setCamera);
    /// <summary>
    /// カメラ開放
    /// </summary>
    ~CameraObserver();
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>編集カメラの向き</returns>
    VECTOR GetCameraDir()const;
    /// <summary>
    /// 引数のものがカメラの範囲内か調べる
    /// </summary>
    /// <param name="obj">調べたいオブジェクト</param>
    /// <returns>カメラの範囲内ならTrue</returns>
    bool IsLookingCamera(const Object* const obj) const;
private:
    //編集時のカメラ
    std::shared_ptr<Camera> camera;
};
