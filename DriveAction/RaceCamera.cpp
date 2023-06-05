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
    VECTOR pos = playerObserver->GetSubPos();
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
    //�����̍X�V cameraSpeed�̑��x�ŎԂ̌����ɍ��킹�Ă���
    VECTOR tempDir = VScale(VSub(playerObserver->GetSubDir(), direction), cameraSpeed);
    direction = VNorm(VAdd(direction, tempDir));
    //�J�����̈ʒu�̍X�V
    position = playerObserver->GetSubPos();
    position.y += posY;
    position.x += -(direction.x * targetBetween);
    position.z += -(direction.z * targetBetween);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetween));

    //�ʒu���m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
