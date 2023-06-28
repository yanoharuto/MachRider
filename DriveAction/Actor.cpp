#include "Object.h"
#include "Actor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
Actor::Actor()

    :modelHandle(-1),
    velocity({})
{
}

Actor::Actor(ObjectInit::InitObjKind kind)
{
    objState = sleep;
    InitParamater(kind);
};
/// <summary>
/// �`��
/// </summary>
void Actor::Draw() const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //�ύX�O�̍s���ۑ�
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    //������ς���
    ModelSetMatrix();
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, position);
    //�T�C�Y�ύX
    MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
    MV1DrawModel(modelHandle);
    //�s������ɖ߂�
    MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// ���x����
// </summary>
/// <returns></returns>
VECTOR Actor::GetVelocity()
{

    return velocity;

}
/// <summary>
/// �����蔻��œ������Ă���n�����
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
/// <summary>
/// ���̃I�u�W�F�N�g�ɓ������Ă邩���ׂ�p�̏��
/// </summary>
/// <returns></returns>
ArgumentConflictResultInfo Actor::GetConflictArgumentInfo()
{
    ArgumentConflictResultInfo resultInfo;
    resultInfo.SetObjInfo(this);
    return resultInfo;
}
/// <summary>
/// �`�惂�f���̍s����Z�b�g
/// </summary>
void Actor::ModelSetMatrix() const
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// �R���X�g���N�^�ŌĂ΂�鏈��
/// </summary>
void Actor::InitParamater(ObjectInit::InitObjKind kind)
{
    ActorParameter initParam = InitActor::GetActorParamator(kind);
    //�A�Z�b�g�������Ă���
    modelHandle = initParam.modelHandle;
    //�|�W�V����
    position = {};
    position.y = initParam.firstPosY;
    //����
    direction = { 1,0,0 };
    //���˕Ԃ��
    bouncePower = initParam.setBouncePow;
    //���a
    radius = initParam.setRadius;
    //model�̑傫��
    modelSize = initParam.setModelSize;
}
/// <summary>
/// �ʒu�������Velocity�ɍ��킹�čX�V����
/// </summary>
void Actor::ReflectsVelocity()
{
    // �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // �|�W�V�������X�V.
    position = VAdd(position, velocity);
}
