#include "DrawModel.h"
#include "DxLib.h"
#include "Object.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// model�̕`��������
/// </summary>
DrawModel::DrawModel(ObjectInit::InitObjKind kind)
{
    modelHandle = InitActor::GetModelHandle(kind);
}

/// <summary>
/// model�̑傫���ɍ��킹�ĕ`�悷��
/// </summary>
/// <param name="drawObj">�ʒu�Ƃ��傫���Ƃ������Ă����炤</param>
void DrawModel::Draw(Object* const drawObj) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle != -1)
    {
        //������ς���
        ModelSetMatrix(drawObj);
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, drawObj->GetPos());
        //�`��
        MV1DrawModel(modelHandle);
    }
}

/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
void DrawModel::ModelSetMatrix(Object* const drawObj) const
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, drawObj->GetDir(), VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}