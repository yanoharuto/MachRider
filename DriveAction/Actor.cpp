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
    InitParamater(kind);
};

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

VECTOR Actor::GetVelocity()
{

    return velocity;

}

HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}

ArgumentConflictResultInfo Actor::GetConflictArgumentInfo()
{
    ArgumentConflictResultInfo resultInfo;
    resultInfo.SetObjInfo(this);
    return resultInfo;
}

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
