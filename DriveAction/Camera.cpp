#include "Camera.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "CSVFileLoader.h"
#include "Utility.h"
//カメラの画角
float Camera::lookingDeg = 0;

using namespace InitCamera;
/// <summary>
/// カメラの速度や高さの初期化
/// </summary>
/// <param name="type">どのタイミングで使うか教えて</param>
Camera::Camera(UseCameraSceneKind type)
{
    //初期化
    LoadData(type);
}

Camera::~Camera()
{
}
/// <summary>
/// カメラの範囲内か調べる
/// </summary>
/// <param name="actor">調べたいオブジェクト</param>
/// <returns></returns>
bool Camera::IsLookingCamera(const Actor* const actor) const
{
    VECTOR between = VSub(actor->GetPos(), position);
    return OriginalMath::GetDegreeMisalignment(between, direction) < lookingDeg;
}
/// <summary>
/// 初期化情報所得
/// </summary>
/// <param name="type">シーンによってカメラの性能を変える</param>
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