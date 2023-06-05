#include "Camera.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "CSVFileLoader.h"
#include "Utility.h"
std::unordered_map<VECTOR*, VECTOR*> Camera::cameraPosDir;
float Camera::lookingDeg = 0;
using namespace InitParamater;
Camera::Camera(CameraType type)
{
    LoadData(type);
    pPosition = &position;
    pDirection = &direction;
    cameraPosDir.insert(std::make_pair(pPosition, pDirection));
}

Camera::~Camera()
{
}

bool Camera::IsLookingCamera(const Actor* actor)
{
    for (auto itr = cameraPosDir.begin(); itr != cameraPosDir.end(); itr++)
    {
        VECTOR between = VSub(actor->GetPos(), *(*itr).first);
        return OriginalMath::GetDegreeMisalignment(between, *(*itr).second) < lookingDeg;
    }
    return false;
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