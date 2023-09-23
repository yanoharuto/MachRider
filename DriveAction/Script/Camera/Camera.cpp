#include "Camera.h"
#include "Actor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
//カメラの画角
float Camera::lookingAngle = 0;
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
/// カメラの向きを所得
/// </summary>
/// <returns>カメラの向きベクトル</returns>
VECTOR Camera::GetNormDirection()const
{
    return direction;
}
/// <summary>
/// カメラの位置
/// </summary>
/// <returns>カメラの座標</returns>
VECTOR Camera::GetPosition() const
{
    return position;
}
/// <summary>
/// 見える角度を所得
/// </summary>
/// <returns></returns>
float Camera::GetLookingAngle() const
{
    return lookingAngle;
}
/// <summary>
/// 初期化情報所得
/// </summary>
/// <param name="type">シーンによってカメラの性能を変える</param>
void Camera::LoadData(UseCameraSceneKind type)
{
    //カメラ情報まとめファイルを所得
    CSVFileLoader* initFileLoader = new CSVFileLoader(initFileName);
    auto strData = initFileLoader->GeFileStringData();
    //まとめファイルからシーンごとの情報を所得
    CSVFileLoader* initDataLoader = new CSVFileLoader(strData[static_cast<int>(type)]);
    strData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initFileLoader);
    using enum CameraParameter;
    //カメラの有効範囲
    float nearValue = STR_TO_F(strData[static_cast<int>(setNearValue)]);
    float farValue = STR_TO_F(strData[static_cast<int>(setFarValue)]);
    SetCameraNearFar(nearValue, farValue);
    //ターゲットとの距離
    targetBetweenSize = STR_TO_F(strData[static_cast<int>(setTargetBetween)]);
    //高度
    posY = STR_TO_F(strData[static_cast<int>(setYPosition)]);
    //カメラの速さ
    cameraSpeed = STR_TO_F(strData[static_cast<int>(setCameraSpeed)]);
    //カメラの見えている範囲
    lookingAngle = STR_TO_F(strData[static_cast<int>(setLookingAngle)]);

    SAFE_DELETE(initDataLoader);
}