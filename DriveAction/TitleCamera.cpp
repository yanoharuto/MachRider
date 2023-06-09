#include "TitleCamera.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"

/// <summary>
/// タイトル画面のカメラ　車の斜め正面を映す
/// </summary>
TitleCamera::TitleCamera(std::shared_ptr<ObjectObserver> target)
    :Camera(InitCamera::title)
{
    targetObserver = target;
    VECTOR pos = targetObserver.lock()->GetSubjectPos();
    position = { 0,posY,0 };
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// プレイヤーの位置に合わせてカメラの位置を修正
/// </summary>
void TitleCamera::Update()
{
    //カメラの位置　ちょっと離れる
    VECTOR pos = VAdd(targetObserver.lock()->GetSubjectPos(), VScale(targetObserver.lock()->GetSubjectDir(), targetBetween));
    //車の向きから若干ずらしてさらに離れる
    VECTOR between = VScale(OriginalMath::GetYRotateVector(targetObserver.lock()->GetSubjectDir(),cameraRotate),targetBetween);
    position = VAdd(pos, between);
    position.y = posY;
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
