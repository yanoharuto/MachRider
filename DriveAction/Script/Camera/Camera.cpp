#include "Camera.h"
#include "Actor.h"
#include "CameraManager.h"
#include "Utility.h"
//�J�����̉�p
float Camera::lookingAngle = 0;
using namespace InitCamera;
/// <summary>
/// �J�����̑��x�⍂���̏�����
/// </summary>
/// <param name="type">�ǂ̃^�C�~���O�Ŏg����������</param>
Camera::Camera(UseCameraSceneKind type)
{
    //������
    LoadData(type);
}

/// <summary>
/// �J�����̌���������
/// </summary>
/// <returns>�J�����̌����x�N�g��</returns>
VECTOR Camera::GetNormDirection()const
{
    return direction;
}
/// <summary>
/// �J�����̈ʒu
/// </summary>
/// <returns>�J�����̍��W</returns>
VECTOR Camera::GetPosition() const
{
    return position;
}
/// <summary>
/// ������p�x������
/// </summary>
/// <returns></returns>
float Camera::GetLookingAngle() const
{
    return lookingAngle;
}
/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
void Camera::LoadData(UseCameraSceneKind type)
{
    //�J�������܂Ƃ߃t�@�C��������
    CameraManager* manager = new CameraManager();
    CameraManager::CameraParamater paramater = manager->GetCameraParamator(type);
    //�J�����̗L���͈�
    float nearValue = paramater.nearValue;
    float farValue = paramater.farValue;
    SetCameraNearFar(nearValue, farValue);
    //�^�[�Q�b�g�Ƃ̋���
    targetBetweenSize = paramater.targetBetween;
    //���x
    posY = paramater.setYPos;
    //�J�����̑���
    cameraSpeed = paramater.speed;
    //�J�����̌����Ă���͈�
    lookingAngle = paramater.lookAngle;
}