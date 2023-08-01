#include "ConflictProcessor.h"
#include "Actor.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
/// <summary>
/// �Փˏ������s��
/// </summary>
/// <param name="obj">���s�������Փˏ���������I�u�W�F�N�g</param>
ConflictProcessor::ConflictProcessor(Actor* const obj)
{
    object = obj;
}

/// <summary>
/// �����蔻��̏������Ăяo��
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProcessor::ConflictProcess(ConflictExamineResultInfo resultInfo)
{
    //�Փˌ�̏������s���K�v���Ȃ��Ȃ�I��
    if (object == nullptr)return;

    if (resultInfo.hit != HitSituation::NotHit)
    {
        //�����������̏������s��
        object->ConflictProcess(resultInfo);
    }
}
/// <summary>
/// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
