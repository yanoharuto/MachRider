#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
VECTOR EditorCamera::staticDir;
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
/// カメラ操作
/// </summary>
void EditorCamera::Update()
{
    if (UserInput::GetInputState(AKey) == Hold)//Akeyを押している間はカメラ操作
    {
        //右左で向き変更
        if (UserInput::GetInputState(Left))direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
        if (UserInput::GetInputState(Right))direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
        //上下で移動
        if (UserInput::GetInputState(Up))position = VAdd(position, VScale(direction, cameraSpeed));
        if (UserInput::GetInputState(Down))position = VAdd(position, VScale(direction, -cameraSpeed));
    }
    targetBetween = VSize(VSub(StageDataEditor::GetEditObjPos(), position));
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(StageDataEditor::GetEditObjPos(), VScale(direction, targetBetween));
    aimPos.y = 0;
    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
    staticDir = direction;
}
/// <summary>
/// 向き
/// </summary>
/// <returns></returns>
VECTOR EditorCamera::GetNormDirection()
{
    return staticDir;
}
