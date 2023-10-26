#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
/// <summary>
/// Editor��ʂ̃J����
/// </summary>
EditorCamera::EditorCamera()
    :Camera(CameraDataLoader::UseCameraSceneKind::editor)
{
    position = {};
    position.y = posY;
    direction = VGet(1,0,0);
}
/// <summary>
/// �J�����̌���ׂ�������ύX
/// </summary>
/// <param name="targetPlaceData">���������ꏊ�̔z�u���</param>
void EditorCamera::UpdatePositionAndTarget(PlacementData targetPlaceData)
{
    //�J�����̑_���Ă���W
    VECTOR placePos = VGet(targetPlaceData.posX, 0, targetPlaceData.posZ);
    position = VAdd(placePos, VScale(direction, targetBetweenSize));
    position.y = posY;
    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, placePos);
}
/// <summary>
/// �㉺���E�L�[�Ō����ƃ^�[�Q�b�g�܂ł̋�����ύX����
/// </summary>
void EditorCamera::UpdateDirectionAndTargetBetween()
{
    //�E���Ō����ύX
    if (UserInput::GetInputState(UserInput::KeyInputKind::Left) != UserInput::InputState::Free)
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Right) != UserInput::InputState::Free)
    {
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    }

    //�㉺�ňړ�
    if (UserInput::GetInputState(UserInput::KeyInputKind::Up) != UserInput::InputState::Free)
    {
        //�������k�߂�
        targetBetweenSize -= cameraSpeed;
        if (targetBetweenSize < cameraSpeed)
        {
            targetBetweenSize = cameraSpeed;
        }
    }
    else if (UserInput::GetInputState(UserInput::KeyInputKind::Down) != UserInput::InputState::Free)
    {
        //������b��
        targetBetweenSize += cameraSpeed;
    }
}
