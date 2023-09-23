#include "Camera.h"
#include "Actor.h"
#include "CSVFileLoader.h"
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
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    auto strData = initFileLoader->GeFileStringData();
    //�܂Ƃ߃t�@�C������V�[�����Ƃ̏�������
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[static_cast<int>(type)]);
    strData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initFileLoader);
    using enum CameraParameter;
    //�J�����̗L���͈�
    float nearValue = STR_TO_F(strData[static_cast<int>(setNearValue)]);
    float farValue = STR_TO_F(strData[static_cast<int>(setFarValue)]);
    SetCameraNearFar(nearValue, farValue);
    //�^�[�Q�b�g�Ƃ̋���
    targetBetweenSize = STR_TO_F(strData[static_cast<int>(setTargetBetween)]);
    //���x
    posY = STR_TO_F(strData[static_cast<int>(setYPosition)]);
    //�J�����̑���
    cameraSpeed = STR_TO_F(strData[static_cast<int>(setCameraSpeed)]);
    //�J�����̌����Ă���͈�
    lookingAngle = STR_TO_F(strData[static_cast<int>(setLookingAngle)]);

    SAFE_DELETE(initDataLoader);
}