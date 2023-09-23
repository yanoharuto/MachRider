#include "CameraObserver.h"
#include "Camera.h"
#include "OriginalMath.h"
#include "Object.h"
/// <summary>
/// �J���������L���Ă��炤
/// </summary>
/// <param name="setCamera">���L���Ă��炤�J����</param>
CameraObserver::CameraObserver(std::shared_ptr<Camera> setCamera)
{
    camera = setCamera;
}
/// <summary>
/// �J�����J��
/// </summary>
CameraObserver::~CameraObserver()
{
    camera.reset();
}
/// <summary>
/// �J�����̌���������
/// </summary>
/// <returns>�ҏW�J�����̌���</returns>
VECTOR CameraObserver::GetCameraDir() const
{
    return camera->GetNormDirection();
}

/// <summary>
/// �����̂��̂��J�����͈͓̔������ׂ�
/// </summary>
/// <param name="obj">���ׂ����I�u�W�F�N�g</param>
/// <returns>�J�����͈͓̔��Ȃ�True</returns>
bool CameraObserver::IsLookingCamera(const Object* const obj) const
{
    VECTOR between = VSub(obj->GetPos(), camera->GetPosition());
    return OriginalMath::GetDegreeMisalignment(between, camera->GetNormDirection()) < camera->GetLookingAngle();
}