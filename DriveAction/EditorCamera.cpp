#include "EditorCamera.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "StageDataEditor.h"
VECTOR EditorCamera::staticDir;
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
/// �J��������
/// </summary>
void EditorCamera::Update()
{
    if (UserInput::GetInputState(AKey) == Hold)//Akey�������Ă���Ԃ̓J��������
    {
        //�E���Ō����ύX
        if (UserInput::GetInputState(Left))direction = VNorm(OriginalMath::GetYRotateVector(direction, -rotaSpeed));
        if (UserInput::GetInputState(Right))direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
        //�㉺�ňړ�
        if (UserInput::GetInputState(Up))position = VAdd(position, VScale(direction, cameraSpeed));
        if (UserInput::GetInputState(Down))position = VAdd(position, VScale(direction, -cameraSpeed));
    }
    targetBetween = VSize(VSub(StageDataEditor::GetEditObjPos(), position));
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(StageDataEditor::GetEditObjPos(), VScale(direction, targetBetween));
    aimPos.y = 0;
    //�ʒu�ƌ������m��
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
    staticDir = direction;
}
/// <summary>
/// ����
/// </summary>
/// <returns></returns>
VECTOR EditorCamera::GetNormDirection()
{
    return staticDir;
}
