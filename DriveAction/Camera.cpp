#include "Camera.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "CSVFileLoader.h"
#include "Utility.h"

float Camera::lookingDeg = 0;
using namespace InitCamera;
Camera::Camera(UseCameraSceneKind type)
{
    LoadData(type);
}

Camera::~Camera()
{
}

bool Camera::IsLookingCamera(const Actor* const actor) const
{
    VECTOR between = VSub(actor->GetPos(), position);
    return OriginalMath::GetDegreeMisalignment(between, direction) < lookingDeg;
}
/// <summary>
/// ��������񏊓�
/// </summary>
/// <param name="type"></param>
void Camera::LoadData(UseCameraSceneKind type)
{
    //�Z�߃t�@�C��������
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    std::vector<const char*> loadData = initFileLoader->GetLoadCharData();
    //�Z�߃t�@�C������V�[�����̏�������
    CSVFileLoader* initDataLoader = new CSVFileLoader(loadData[type]);
    loadData = initDataLoader->GetLoadCharData();
    SAFE_DELETE(initFileLoader);
    //�J�����̗L���͈�
    SetCameraNearFar(atof(loadData[setNearValue]), atof(loadData[setFarValue]));
    //�^�[�Q�b�g�Ƃ̋���
    targetBetween = atof(loadData[setTargetBetween]);
    //���x
    posY = atof(loadData[setYPosition]);
    //�J�����̑���
    cameraSpeed = atof(loadData[setCameraSpeed]);
    //�J�����̌����Ă���͈�
    lookingDeg = atof(loadData[setLookingDegree]);

    SAFE_DELETE(initDataLoader);
}