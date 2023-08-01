#include "EditorModelViewer.h"
#include "OriginalMath.h"
#include "EditorObject.h"
#include "InitActor.h"
/// <summary>
/// �e�ҏW�I�u�W�F�N�g�̕`��S����
/// </summary>
EditorModelViewer::EditorModelViewer(ObjectInit::InitObjKind kind)
    :ModelViewer(kind)
{
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    mSize = initParam.setModelSize;
}
/// <summary>
/// �����̏ꏊ�ɕ`��
/// </summary>
/// <param name="data"></param>
void EditorModelViewer::Draw(EditArrangementData data) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //������ς���
    ModelSetMatrix(VGet(data.dirX,0,data.dirZ));
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, VGet(data.posX,0,data.posZ));
    //�T�C�Y�ύX
    MV1SetScale(modelHandle, VGet(mSize, mSize, mSize));
    MV1DrawModel(modelHandle);
}
/// <summary>
/// �ҏW�҂��I�����Ă��镨�̕\���@�኱��ɏオ��
/// </summary>
/// <param name="data"></param>
void EditorModelViewer::SelectDraw(EditArrangementData data) const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //������ς���
    ModelSetMatrix(VGet(data.dirX, 0, data.dirZ));
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, VGet(data.posX, selectPosY, data.posZ));
    //�T�C�Y�ύX
    MV1SetScale(modelHandle, VGet(mSize, mSize, mSize));
    MV1DrawModel(modelHandle);
}
/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
/// <param name="dir"></param>
void EditorModelViewer::ModelSetMatrix(VECTOR dir) const
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}