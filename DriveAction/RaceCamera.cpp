#include "RaceCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Utility.h"
#include "UserInput.h"
/// <summary>
/// �V��ł���Ƃ��̃J�����̏�����
/// </summary>
/// <param name="player">�v���C���[�̈ʒu</param>
RaceCamera::RaceCamera(std::weak_ptr<ObjectObserver> target)
    :Camera(InitCamera::game)
{
    targetObserver = target;
    VECTOR pos = targetObserver.lock()->GetSubjectPos();
    position = {0,pos.y,0};
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// �ʒu������̍X�V
/// </summary>
void RaceCamera::Update()
{
    VECTOR subVec = VSub(targetObserver.lock()->GetSubjectDir(), direction);
    subVec.y = 0;
    //�����̍X�V cameraSpeed�̑��x�ŎԂ̌����ɍ��킹�Ă���
    VECTOR tempDir = VScale(subVec, cameraSpeed * VSize(subVec));
    direction = VNorm(VAdd(direction, tempDir));
    //�J�����̈ʒu�̍X�V
    position = targetObserver.lock()->GetSubjectPos();
    position.y = posY;
    position.x += -(direction.x * targetBetween);
    position.z += -(direction.z * targetBetween);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetween));

    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
