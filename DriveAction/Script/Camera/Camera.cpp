#include "Camera.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "CSVFileLoader.h"
#include "Utility.h"
//�J�����̉�p
float Camera::lookingDeg = 0;

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
/// �����̂��̂��J�����͈͓̔������ׂ�
/// </summary>
/// <param name="actor">���ׂ����I�u�W�F�N�g</param>
/// <returns>�J�����͈͓̔��Ȃ�True</returns>
bool Camera::IsLookingCamera(const Actor* const actor) const
{
    VECTOR between = VSub(actor->GetPos(), position);
    return OriginalMath::GetDegreeMisalignment(between, direction) < lookingDeg;
}
/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type">�V�[���ɂ���ăJ�����̐��\��ς���</param>
void Camera::LoadData(UseCameraSceneKind type)
{
    //�J�������܂Ƃ߃t�@�C��������
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    auto strData = initFileLoader->GetLoadStringData();
    //�܂Ƃ߃t�@�C������V�[�����Ƃ̏�������
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[type]);
    strData = initDataLoader->GetLoadStringData();
    SAFE_DELETE(initFileLoader);
    //�J�����̗L���͈�
    float nearValue = SAFE_STR_TO_F(strData[setNearValue]);
    float farValue = SAFE_STR_TO_F(strData[setFarValue]);
    SetCameraNearFar(nearValue, farValue);
    //�^�[�Q�b�g�Ƃ̋���
    targetBetween = SAFE_STR_TO_F(strData[setTargetBetween]);
    //���x
    posY = SAFE_STR_TO_F(strData[setYPosition]);
    //�J�����̑���
    cameraSpeed = SAFE_STR_TO_F(strData[setCameraSpeed]);
    //�J�����̌����Ă���͈�
    lookingDeg = SAFE_STR_TO_F(strData[setLookingDegree]);

    SAFE_DELETE(initDataLoader);
}