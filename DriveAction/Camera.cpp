#include "Camera.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "CSVFileLoader.h"
#include "Utility.h"

float Camera::lookingDeg = 0;
using namespace InitCamera;
Camera::Camera(CameraType type)
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

void Camera::LoadData(CameraType type)
{
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    std::vector<const char*> loadData = initFileLoader->GetLoadCharData();

    CSVFileLoader* initDataLoader = new CSVFileLoader(loadData[type]);
    loadData = initDataLoader->GetLoadCharData();
    SAFE_DELETE(initFileLoader);

    SetCameraNearFar(atof(loadData[setNearValue]), atof(loadData[setFarValue]));
    targetBetween = atof(loadData[setTargetBetween]);
    posY = atof(loadData[setYBetween]);
    cameraSpeed = atof(loadData[setCameraSpeed]);
    lookingDeg = atof(loadData[setLookingDegree]);

    SAFE_DELETE(initDataLoader);
}