#include "Object.h"
#include "Actor.h"
#include "OriginalMath.h"
#include "InitActor.h"
#include "AssetManager.h"
/// <summary>
/// �`����@��ύX����Ȃ�������ɓn���Ă�������
/// </summary>
/// <param name="kind"></param>
Actor::Actor(ObjectInit::InitObjKind kind)
    :Object(kind)
{
    objState = sleep;
}

/// <summary>
/// �����蔻��œ������Ă���n�����
/// </summary>
/// <returns></returns>
HitCheckInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}
/// <summary>
///�@�Q�[���J�n���������B�I�[�o�[���C�h���Ȃ���Ε��ʂ̍X�V
/// </summary>
void Actor::PrepareGame()
{
    Update();
}