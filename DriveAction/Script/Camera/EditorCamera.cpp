#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
/// <summary>
/// Editor画面のカメラ
/// </summary>
EditorCamera::EditorCamera()
    :Camera(InitCamera::editor)
{
    position = {};
    position.y = posY;
    direction = VGet(1,0,0);
}
/// <summary>
/// 上下左右キーで動かすことが出来る
/// </summary>
/// <param name="targetPlaceData">向きたい場所の配置情報</param>
void EditorCamera::Update(PlacementData targetPlaceData)
{
    //右左で向き変更
    if (UserInput::GetInputState(Left))
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
    }
    if (UserInput::GetInputState(Right))
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    }
    //上下で移動
    if (UserInput::GetInputState(Up))
    {
        position = VAdd(position, VScale(direction, cameraSpeed));
    }
    if (UserInput::GetInputState(Down))
    {
        position = VAdd(position, VScale(direction, -cameraSpeed));
    }
    VECTOR placePos = VGet(targetPlaceData.posX, 0, targetPlaceData.posZ);
    VECTOR placeDir = VGet(targetPlaceData.dirX, 0, targetPlaceData.dirZ);
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(direction, VScale(placeDir, targetBetweenSize));
    aimPos.y = 0;
    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}

/// <summary>
/// カメラの向きを所得
/// </summary>
/// <returns>カメラの向きベクトル</returns>
VECTOR EditorCamera::GetNormDirection()
{
    return direction;
}