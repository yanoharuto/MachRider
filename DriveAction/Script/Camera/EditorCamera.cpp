#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
/// <summary>
/// Editor画面のカメラ
/// </summary>
EditorCamera::EditorCamera()
    :Camera(CameraDataLoader::UseCameraSceneKind::editor)
{
    position = {};
    position.y = posY;
    direction = VGet(1,0,0);
}
/// <summary>
/// カメラの見るべき向きを変更
/// </summary>
/// <param name="targetPlaceData">向きたい場所の配置情報</param>
void EditorCamera::UpdatePositionAndTarget(PlacementData targetPlaceData)
{
    //カメラの狙ってる座標
    VECTOR placePos = VGet(targetPlaceData.posX, 0, targetPlaceData.posZ);
    position = VAdd(placePos, VScale(direction, targetBetweenSize));
    position.y = posY;
    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, placePos);
}
/// <summary>
/// 上下左右キーで向きとターゲットまでの距離を変更する
/// </summary>
void EditorCamera::UpdateDirectionAndTargetBetween()
{
    //右左で向き変更
    if (UserInput::GetInputState(UserInput::KeyInputKind::Left) != UserInput::InputState::Free)
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) != UserInput::InputState::Free)
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    }

    //上下で移動
    if (UserInput::GetInputState(UserInput::KeyInputKind::Up) != UserInput::InputState::Free)
    {
        //距離を縮める
        targetBetweenSize -= cameraSpeed;
        if (targetBetweenSize < cameraSpeed)
        {
            targetBetweenSize = cameraSpeed;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) != UserInput::InputState::Free)
    {
        //距離を話す
        targetBetweenSize += cameraSpeed;
    }
}
