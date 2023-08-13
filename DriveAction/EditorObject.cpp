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
EditorObject::EditorObject(ObjectInit::InitObjKind kind)
    :Actor(kind)
{
    objKind = kind;
}
/// <summary>
/// �ʒu�������ύX������Ԃ�
/// </summary>
/// <param name="editData"></param>
EditorObject::EditorObject(EditArrangementData editData)
    :Actor(static_cast<ObjectInit::InitObjKind>(editData.objKind))
{
    objKind = static_cast<ObjectInit::InitObjKind>(editData.objKind);
    position = VGet(editData.posX, 0, editData.posZ);
    direction = VGet(editData.dirX, 0, editData.dirZ);
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
/// �I�u�W�F�N�g�̈ʒu���]�Ȃǂ�n��
/// </summary>
/// <returns></returns>
EditArrangementData EditorObject::GetEditObjectData() const
{
    EditArrangementData data;
    data.dirX = direction.x;
    data.dirZ = direction.z;
    data.posX = position.x;
    data.posZ = position.z;
    data.objKind = objKind;
    return data;
}
/// <summary>
/// ���͂𔽉f���Ĉړ��Ɖ�]���X�V
/// </summary>
void EditorObject::ReflectInput()
{
    if (UserInput::GetInputState(WKey) == Hold)//���L�[�������Ă����]���[�h
    {
        float rotate = 0;
        if (UserInput::GetInputState(Left) == Hold)rotate = -rotaSpeed;
        else if (UserInput::GetInputState(Right) == Hold)rotate = +rotaSpeed;
        
        direction = OriginalMath::GetYRotateVector(direction, rotate);

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
