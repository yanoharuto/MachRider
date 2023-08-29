#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EditorCamera.h"
//�ړ����x
const int EditorObject::moveSpeed;
//��]���x
const int EditorObject::rotaSpeed;

/// <summary>
/// �G�f�B�^��Ŏg�p����I�u�W�F�N�g
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
}

EditorObject::~EditorObject()
{
}
/// <summary>
/// �e�I�u�W�F�N�g�𓮂��������]�������肷��
/// </summary>
void EditorObject::Update()
{
    ReflectInput();
}
/// <summary>
/// �`��ɕK�v�ȍ\���̂�n��
/// </summary>
/// <returns>�ʒu�ƌ����ƕ`�悵�����I�u�W�F�N�g�̎��</returns>
PlacementData EditorObject::GePlacementData() const
{
    PlacementData data;
    //����
    data.dirX = direction.x;
    data.dirZ = direction.z;
    //�|�W�V����
    data.posX = position.x;
    data.posZ = position.z;
    return data;
}
/// <summary>
/// �����̔z�u�������p���ʒu��ς���
/// </summary>
/// <param name="setData">�z�u</param>
void EditorObject::SetArrangementData(PlacementData setData)
{
    position = VGet(setData.posX, 0, setData.posZ);
    direction = VGet(setData.dirX, 0, setData.dirZ);
}
/// <summary>
/// ���͂𔽉f���Ĉړ��Ɖ�]���X�V
/// </summary>
void EditorObject::ReflectInput()
{
    if (UserInput::GetInputState(WKey) == Hold)//���L�[�������Ă����]���[�h
    {
       
        //���E�L�[�������Ɖ�]����
        if (UserInput::GetInputState(Left) == Hold)
        {
           direction = OriginalMath::GetYRotateVector(direction, -rotaSpeed);
        }
        else if (UserInput::GetInputState(Right) == Hold)
        {
            direction = OriginalMath::GetYRotateVector(direction, rotaSpeed);
        }
    }
    else //�����ĂȂ�������ړ����[�h
    {
        //�J�����̌����ɍ��킹�Ĉړ�
        VECTOR cameraDir = EditorCamera::GetNormDirection();

        if (UserInput::GetInputState(Left) == Hold)//���ړ�
        {
            cameraDir = VCross(cameraDir, VGet(0, 1, 0));
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        else if (UserInput::GetInputState(Right) == Hold)//�E�ړ�
        {
            cameraDir = VCross(cameraDir, VGet(0, -1, 0));
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        if (UserInput::GetInputState(Up) == Hold)//�O�ړ�
        {
            cameraDir = VScale(cameraDir, moveSpeed);
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        else if (UserInput::GetInputState(Down) == Hold)//���ړ�
        {
            cameraDir = VScale(cameraDir, -moveSpeed);
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
    }
}
