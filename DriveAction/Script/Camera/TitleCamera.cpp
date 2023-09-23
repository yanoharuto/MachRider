#include "TitleCamera.h"
#include "ObjectObserver.h"
#include "OriginalMath.h"

/// <summary>
/// �^�C�g����ʂ̃J�����@�Ԃ̎΂ߐ��ʂ��f��
/// </summary>
TitleCamera::TitleCamera(std::shared_ptr<ObjectObserver> target)
    :Camera(InitCamera::UseCameraSceneKind::title)
{
    targetObserver = target;
    VECTOR pos = targetObserver.lock()->GetSubjectPos();
    position = { 0,posY,0 };
    SetCameraPositionAndTarget_UpVecY(position, pos);
}
/// <summary>
/// �v���C���[�̈ʒu�ɍ��킹�ăJ�����̈ʒu���C��
/// </summary>
void TitleCamera::Update()
{
    //�J�����̌����ʒu
    VECTOR aimPos = targetObserver.lock()->GetSubjectPos();
    //�Ԃ̌�������኱���炵�Ă���ɗ����
    VECTOR between = VScale(OriginalMath::GetYRotateVector(targetObserver.lock()->GetSubjectDir(),cameraRotate),targetBetweenSize);
    position = VAdd(VAdd(aimPos, VScale(targetObserver.lock()->GetSubjectDir(), targetBetweenSize)), between);
    position.y = posY;
    //�J�����̌�����ύX
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}
