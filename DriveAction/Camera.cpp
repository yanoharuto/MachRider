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
/// 初期化情報所得
/// </summary>
/// <param name="type"></param>
void Camera::LoadData(UseCameraSceneKind type)
{
    //纏めファイルを所得
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    std::vector<const char*> loadData = initFileLoader->GetLoadCharData();
    //纏めファイルからシーン毎の情報を所得
    CSVFileLoader* initDataLoader = new CSVFileLoader(loadData[type]);
    loadData = initDataLoader->GetLoadCharData();
    SAFE_DELETE(initFileLoader);
    //カメラの有効範囲
    SetCameraNearFar(atof(loadData[setNearValue]), atof(loadData[setFarValue]));
    //ターゲットとの距離
    targetBetween = atof(loadData[setTargetBetween]);
    //高度
    posY = atof(loadData[setYPosition]);
    //カメラの速さ
    cameraSpeed = atof(loadData[setCameraSpeed]);
    //カメラの見えている範囲
    lookingDeg = atof(loadData[setLookingDegree]);

    SAFE_DELETE(initDataLoader);
}