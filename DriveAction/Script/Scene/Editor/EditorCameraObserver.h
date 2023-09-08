#pragma once
#include <memory>
#include <iostream>
#include "DxLib.h"

class EditorCamera;
/// <summary>
/// カメラの向きをオブジェクトに渡すためのクラス
/// </summary>
class EditorCameraObserver
{
public:
    /// <summary>
    /// カメラを共有してもらう
    /// </summary>
    /// <param name="editorCamera">共有してもらうカメラ</param>
    EditorCameraObserver(std::shared_ptr<EditorCamera> editorCamera);
    /// <summary>
    /// カメラ開放
    /// </summary>
    ~EditorCameraObserver();
    /// <summary>
    /// カメラの向きを所得
    /// </summary>
    /// <returns>編集カメラの向き</returns>
    VECTOR GetCameraDir()const;
private:
    //編集時のカメラ
    std::shared_ptr<EditorCamera> camera;
};

