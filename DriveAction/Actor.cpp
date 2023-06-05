#include "Object.h"
#include "Actor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "Camera.h"
#include "AssetManager.h"
Actor::Actor()

    :modelHandle(-1),
    velocity({})
{
}
using namespace InitParamater;
Actor::Actor(ObjectInit::InitObjKind kind)
{
    ActorParametor initParam = InitActor::GetActorParamator(kind);
    //�A�Z�b�g�������Ă���
    modelHandle = AssetManager::Get3DModelAssetHandle(InitActor::GetActorInitPassData(kind).modelPass);
    //�|�W�V����
    position.y = initParam.firstPosY;
    //���˕Ԃ��
    bouncePower = initParam.setBouncePow;
    //���a
    radius = initParam.setRadius;
    //model�̑傫��
    modelSize = initParam.setModelSize;
};

void Actor::Draw() const
{
    //�`�悷�郂�f�����Ȃ��Ȃ�I��
    if (modelHandle == -1)return;
    //�J�����Ɏʂ�����ɂ���Ȃ�
    if(Camera::IsLookingCamera(this))
    {
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

void Actor::UpdatePosition()
{
    // �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // �|�W�V�������X�V.
    position = VAdd(position, velocity);
}
