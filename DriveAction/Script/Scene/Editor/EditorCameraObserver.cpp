#include "EditorCameraObserver.h"
#include "EditorCamera.h"
/// <summary>
/// �J���������L���Ă��炤
/// </summary>
/// <param name="editorCamera">���L���Ă��炤�J����</param>
EditorCameraObserver::EditorCameraObserver(std::shared_ptr<EditorCamera> editorCamera)
{
    camera = editorCamera;
}
/// <summary>
/// �J�����J��
/// </summary>
EditorCameraObserver::~EditorCameraObserver()
{
    camera.reset();
}
/// <summary>
/// �J�����̌���������
/// </summary>
/// <returns>�ҏW�J�����̌���</returns>
VECTOR EditorCameraObserver::GetCameraDir() const
{
    return camera->GetNormDirection();
}
