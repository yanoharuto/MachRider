#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
/// <summary>
/// Editor��ʂ̃J����
/// </summary>
EditorCamera::EditorCamera()
    :Camera(InitCamera::editor)
{
    position = {};
    position.y = posY;
    direction = VGet(1,0,0);
}
/// <summary>
/// �㉺���E�L�[�œ��������Ƃ��o����
/// </summary>
/// <param name="targetPlaceData">���������ꏊ�̔z�u���</param>
void EditorCamera::Update(PlacementData targetPlaceData)
{
    //�E���Ō����ύX
    if (UserInput::GetInputState(Left))
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
    }
    if (UserInput::GetInputState(Right))
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    }
    //�㉺�ňړ�
    if (UserInput::GetInputState(Up))
    {
        position = VAdd(position, VScale(direction, cameraSpeed));
    }
    if (UserInput::GetInputState(Down))
    {
        position = VAdd(position, VScale(direction, -cameraSpeed));
    }
    VECTOR placePos = VGet(targetPlaceData.posX, 0, targetPlaceData.posZ);
    VECTOR placeDir = VGet(targetPlaceData.dirX, 0, targetPlaceData.dirZ);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(direction, VScale(placeDir, targetBetweenSize));
    aimPos.y = 0;
    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}

/// <summary>
/// �J�����̌���������
/// </summary>
/// <returns>�J�����̌����x�N�g��</returns>
VECTOR EditorCamera::GetNormDirection()
{
    return direction;
}