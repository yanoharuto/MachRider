#include "conflictProccesor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "ConflictManager.h"

ConflictProccesor::ConflictProccesor(Actor* obj)
{
    object = obj;
    ConflictManager::AddConflictObjInfo(this);
}

ConflictProccesor::~ConflictProccesor()
{

}
/// <summary>
/// �����蔻��ŕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProccesor::GetHitExamineCheckInfo() const
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// �����蔻��̏������Ăяo��
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProccesor::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
    //�Փˌ�̏������s���K�v���Ȃ��Ȃ�I��
    if (object == nullptr)return;

    for (auto ite = resultInfo.begin(); ite != resultInfo.end(); ite++)
    {
        if ((*ite).hit != HitSituation::NotHit)
        {
            if (coolTimer.contains((*ite).tag))
            {
                //�N�[���^�C�����߂��Ă��ē������Ă���Ȃ�
                if (coolTimer[(*ite).tag]->IsOverLimitTime())
                {
                    //�����������̏������s��
                    object->ConflictProccess((*ite));
                    IncrementHitCount((*ite).tag);
                }
            }
            else
            {
                //�����������̏������s��
                object->ConflictProccess((*ite));
                IncrementHitCount((*ite).tag);
            }
        }
    }

}
/// <summary>
/// �����蔻��œ���̂��̂ɃN�[���^�C������������ꍇ�^�C�}�[���Z�b�g�o����
/// </summary>
/// <param name="tag">����̎҂̃^�O</param>
/// 
/// <param name="timer">�N�[���^�C���v���p�̃^�C�}�[</param>
void ConflictProccesor::SetCoolTimer(Object::ObjectTag tag,float setCoolTime)
{
    Timer* timer = new Timer(setCoolTime);
    coolTimer.insert(std::make_pair(tag, timer));
}
/// <summary>
/// �����̃^�O�̃I�u�W�F�N�g�ɉ���Ԃ��������Ԃ�
/// </summary>
/// <param name="objTag"></param>
/// <returns></returns>
int ConflictProccesor::GetTagHitCount(Object::ObjectTag objTag)
{
    return hitCountMap[objTag];
}
/// <summary>
/// �������蔻������I�u�W�F�N�g�������Ă��邩
/// </summary>
/// <returns></returns>
bool ConflictProccesor::IsObjectAlive() const
{
    return object->GetObjectState() == Object::active;
}
/// <summary>
/// �����̃I�u�W�F�N�g�̓��������񐔂𑝂₷
/// </summary>
/// <param name="objTag"></param>
void ConflictProccesor::IncrementHitCount(Object::ObjectTag objTag)
{
    //�܂��ǉ��������Ƃ̂Ȃ��^�O�Ȃ瓖�������񐔂��L�^
    if (!hitCountMap.contains(objTag))
    {
        int hitCount = 1;
        hitCountMap.insert(std::make_pair(objTag, hitCount));
    }
    //����Ȃ�Ԃ��������ɉ񐔂𑝂₷
    else
    {
        hitCountMap[objTag]++;
    }
}
