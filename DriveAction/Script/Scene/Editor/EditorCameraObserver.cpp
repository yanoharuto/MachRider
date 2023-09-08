#include "EditorCameraObserver.h"
#include "EditorCamera.h"
/// <summary>
/// カメラを共有してもらう
/// </summary>
/// <param name="editorCamera">共有してもらうカメラ</param>
EditorCameraObserver::EditorCameraObserver(std::shared_ptr<EditorCamera> editorCamera)
{
    camera = editorCamera;
}
/// <summary>
/// カメラ開放
/// </summary>
EditorCameraObserver::~EditorCameraObserver()
{
    camera.reset();
}
/// <summary>
/// カメラの向きを所得
/// </summary>
/// <returns>編集カメラの向き</returns>
VECTOR EditorCameraObserver::GetCameraDir() const
{
    return camera->GetNormDirection();
}
