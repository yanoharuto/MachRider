#include "GameCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "Utility.h"
#include "UserInput.h"
/// <summary>
/// �V��ł���Ƃ��̃J�����̏�����
/// </summary>
/// <param name="player">�v���C���[�̈ʒu</param>
GameCamera::GameCamera(std::weak_ptr<ObjectObserver> target)
    :Camera(InitCamera::game)
{
    targetObserver = target;
    //�ʒu�ƌ�����������
    VECTOR pos = targetObserver.lock()->GetSubjectPos();
    position = {0,pos.y,0};
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// �ʒu������̍X�V
/// </summary>
void GameCamera::Update()
{
    //�J�����ƃv���C���[�̌����̍����׃N�g��
    VECTOR subDirVec = VSub(targetObserver.lock()->GetSubjectDir(), direction);
    subDirVec.y = 0;
    //�����̍X�V cameraSpeed�̑��x�ŎԂ̌����ɍ��킹�Ă���
    VECTOR tempDir = VScale(subDirVec, cameraSpeed * VSize(subDirVec));
    direction = VNorm(VAdd(direction, tempDir));
    //�J�����̈ʒu�̍X�V
    position = targetObserver.lock()->GetSubjectPos();
    position.y = posY;
    position.x += -(direction.x * targetBetweenSize);
    position.z += -(direction.z * targetBetweenSize);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(position, VScale(direction, targetBetweenSize));
    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
