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
/// <summary>
/// 引数のものがカメラの範囲内か調べる
/// </summary>
/// <param name="actor">調べたいオブジェクト</param>
/// <returns>カメラの範囲内ならTrue</returns>
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
    //カメラ情報まとめファイルを所得
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    auto strData = initFileLoader->GetLoadStringData();
    //まとめファイルからシーンごとの情報を所得
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[type]);
    strData = initDataLoader->GetLoadStringData();
    SAFE_DELETE(initFileLoader);
    //カメラの有効範囲
    float nearValue = SAFE_STR_TO_F(strData[setNearValue]);
    float farValue = SAFE_STR_TO_F(strData[setFarValue]);
    SetCameraNearFar(nearValue, farValue);
    //ターゲットとの距離
    targetBetween = SAFE_STR_TO_F(strData[setTargetBetween]);
    //高度
    posY = SAFE_STR_TO_F(strData[setYPosition]);
    //カメラの速さ
    cameraSpeed = SAFE_STR_TO_F(strData[setCameraSpeed]);
    //カメラの見えている範囲
    lookingDeg = SAFE_STR_TO_F(strData[setLookingDegree]);

    SAFE_DELETE(initDataLoader);
}