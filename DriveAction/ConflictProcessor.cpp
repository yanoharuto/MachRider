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
/// <param name="resultInfo">�Փˎ��̌���</param>
void ConflictProcessor::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.hit != HitSituation::NotHit)
    {
        //�����������̏������s��
        object->OnConflict(resultInfo);
    }
}
/// <summary>
/// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
HitCheckInfo ConflictProcessor::GetHitExamineCheckInfo() const
{
    HitCheckInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
