#include "RaceCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"

#include "RacerManager.h"
#include "Utility.h"
RaceCamera::RaceCamera(RacerManager* racerManager)
    :Camera(InitParamater::game)
{
    playerObserver = new ObjectObserver(racerManager->GetPlayerSubject(0));
    VECTOR pos = playerObserver->GetSubjectPos();
    position = {0,pos.y,0};
    SetCameraPositionAndTarget_UpVecY(position, pos);
}

RaceCamera::~RaceCamera()
{
    SAFE_DELETE(playerObserver);
    cameraPosDir.erase(pPosition);
}

void RaceCamera::Update()
{
    //向きの更新 cameraSpeedの速度で車の向きに合わせている
    VECTOR tempDir = VScale(VSub(playerObserver->GetSubjectDir(), direction), cameraSpeed);
    direction = VNorm(VAdd(direction, tempDir));
    //カメラの位置の更新
    position = playerObserver->GetSubjectPos();
    position.y += posY;
    position.x += -(direction.x * targetBetween);
    position.z += -(direction.z * targetBetween);
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetween));

    //位置を確定
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
