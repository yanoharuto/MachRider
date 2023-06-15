#include "RaceCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Utility.h"
#include "UserInput.h"

RaceCamera::RaceCamera(std::shared_ptr<ObjectObserver> target)
    :Camera(InitCamera::game)
{
    playerObserver = target;
    VECTOR pos = playerObserver.lock()->GetSubjectPos();
    position = {0,pos.y,0};
    SetCameraPositionAndTarget_UpVecY(position, pos);
}

RaceCamera::~RaceCamera()
{
    
}

void RaceCamera::Update()
{
    VECTOR subVec = VSub(playerObserver.lock()->GetSubjectDir(), direction);
    subVec.y = 0;
    //�����̍X�V cameraSpeed�̑��x�ŎԂ̌����ɍ��킹�Ă���
    VECTOR tempDir = VScale(subVec, cameraSpeed * VSize(subVec));
    direction = VNorm(VAdd(direction, tempDir));
    //�J�����̈ʒu�̍X�V
    position = playerObserver.lock()->GetSubjectPos();
    position.y = posY;
    position.x += -(direction.x * targetBetween);
    position.z += -(direction.z * targetBetween);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetween));

    //�ʒu���m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
