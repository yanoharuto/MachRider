#include "RaceCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Utility.h"
#include "UserInput.h"
/// <summary>
/// 遊んでいるときのカメラの初期化
/// </summary>
/// <param name="player">プレイヤーの位置</param>
RaceCamera::RaceCamera(std::weak_ptr<ObjectObserver> target)
    :Camera(InitCamera::game)
{
    targetObserver = target;
    VECTOR pos = targetObserver.lock()->GetSubjectPos();
    position = {0,pos.y,0};
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// 位置や向きの更新
/// </summary>
void RaceCamera::Update()
{
    VECTOR subVec = VSub(targetObserver.lock()->GetSubjectDir(), direction);
    subVec.y = 0;
    //向きの更新 cameraSpeedの速度で車の向きに合わせている
    VECTOR tempDir = VScale(subVec, cameraSpeed * VSize(subVec));
    direction = VNorm(VAdd(direction, tempDir));
    //カメラの位置の更新
    position = targetObserver.lock()->GetSubjectPos();
    position.y = posY;
    position.x += -(direction.x * targetBetween);
    position.z += -(direction.z * targetBetween);
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetween));

    //位置と向きを確定
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
