#include "ConflictManager.h"

std::list<ConflictProccesor*> ConflictManager::conflictObjList;
ConflictManager::ConflictManager()
{
    conflictObjList.clear();
}

ConflictManager::~ConflictManager()
{
    conflictObjList.clear();
}
/// <summary>
/// �����蔻���ǉ�
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::AddConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictObjList.push_back(conflictProccesor);
}
/// <summary>
///�@�����蔻������Ȃ��Ă����悤�ɂ���
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::EraceConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    auto procceesor = std::find(conflictObjList.begin(), conflictObjList.end(), conflictProccesor);
    if (procceesor != conflictObjList.end())
    {
        conflictObjList.erase(procceesor);
    }
}
/// <summary>
/// �f�o�b�O�p�̋������蔻���������
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}

/// <summary>
/// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
std::list<ConflictExamineResultInfo> ConflictManager::GetConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    std::list<ConflictExamineResultInfo> nowHitList;
    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        //�����̃I�u�W�F�N�g���̂��̂Ɠ������Ă���X���[
        if (conflictProccesor != (*objIte))
        {
            //�������Ă��邩���ׂ�
            examineResultInfo = (*objIte)->HitCheck(conflictProccesor->GetHitExamineCheckInfo());
            //�Ԃ����Ă���Ȃ�
            if (examineResultInfo.hit != HitSituation::NotHit)
            {
                //������������ǉ�
                nowHitList.push_back(examineResultInfo);
            }
        }
    }
    return nowHitList;
}
/// <summary>
/// �����蔻�������
/// </summary>
void ConflictManager::Update()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        
        (*objIte)->ConflictProccess(GetConflictObjInfo((*objIte)));
    }
}
