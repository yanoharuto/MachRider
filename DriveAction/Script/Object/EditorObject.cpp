#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "CameraObserver.h"
//�ړ����x
const int EditorObject::moveSpeed = 17;
//��]���x
const int EditorObject::rotaSpeed = 2;

/// <summary>
/// �G�f�B�^��Ŏg�p����I�u�W�F�N�g
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
    
}
/// <summary>
/// �e�I�u�W�F�N�g�𓮂��������]�������肷��
/// </summary>
void EditorObject::Update(std::weak_ptr<CameraObserver> cameraObserever)
{
    //���͏��𔽉f
    ReflectInput(cameraObserever);
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
void EditorObject::ReflectInput(std::weak_ptr<CameraObserver> cameraObserever)
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
        VECTOR cameraDir = cameraObserever.lock()->GetCameraDir();
        cameraDir.y = 0;//���s�ړ������ł���
        //�ړ���
        VECTOR moveValue = {};
        if (UserInput::GetInputState(Left) == Hold)//���ړ�
        {
            moveValue = VCross(cameraDir, VGet(0, -moveSpeed, 0));
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(Right) == Hold)//�E�ړ�
        {
            moveValue = VCross(cameraDir, VGet(0, moveSpeed, 0));
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(Up) == Hold)//�O�ړ�
        {
            moveValue = VScale(cameraDir, -moveSpeed);
            position = VAdd(position, moveValue);
        }
        else if (UserInput::GetInputState(Down) == Hold)//���ړ�
        {
            moveValue = VScale(cameraDir, moveSpeed);
            position = VAdd(position, moveValue);
        }
    }
}

