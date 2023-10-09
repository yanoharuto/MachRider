#include "Camera.h"
#include "Actor.h"
#include "CameraManager.h"
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
    CameraManager* manager = new CameraManager();
    CameraManager::CameraParamater paramater = manager->GetCameraParamator(type);
    //カメラの有効範囲
    float nearValue = paramater.nearValue;
    float farValue = paramater.farValue;
    SetCameraNearFar(nearValue, farValue);
    //ターゲットとの距離
    targetBetweenSize = paramater.targetBetween;
    //高度
    posY = paramater.setYPos;
    //カメラの速さ
    cameraSpeed = paramater.speed;
    //カメラの見えている範囲
    lookingAngle = paramater.lookAngle;
}