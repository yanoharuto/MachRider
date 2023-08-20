#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
//�����������ʂ𔽉f������N���X�̃}�b�v
std::unordered_map<ConflictProcessor*,SphereHitChecker*> ConflictManager::processorKeyMap;
//conflictProcessor�����̓����蔻�肩���ׂ邽�߂̃}�b�v
std::unordered_map<SphereHitChecker*, ConflictProcessor*> ConflictManager::hitCheckerKeyMap;
//�������Ă��邩���ׂ�N���X�̃��X�g
std::list<SphereHitChecker*> ConflictManager::hitCheckList;
/// <summary>
/// �����蔻���Z�߂Ă��邽�߂̓z
/// </summary>
ConflictManager::ConflictManager()
{
    processorKeyMap.clear();
    hitCheckerKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// �����蔻��o�^Map�S����
/// </summary>
ConflictManager::~ConflictManager()
{
    processorKeyMap.clear();
    hitCheckerKeyMap.clear();
    hitCheckList.clear();
}
/// <summary>
/// �����蔻��ǉ�
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::AddHitChecker(SphereHitChecker* const hitChecker)
{
    hitCheckList.push_back(hitChecker);
}
/// <summary>
/// �����蔻�����
/// </summary>
/// <param name="hitChecker"></param>
void ConflictManager::EraceHitChecker(SphereHitChecker* const hitChecker)
{
    if(!hitCheckList.empty())
    {
        //�������������蔻�肪����Ȃ�
        auto procceesor = std::find(hitCheckList.begin(), hitCheckList.end(), hitChecker);
        if (procceesor != hitCheckList.end())
        {
            hitCheckList.erase(procceesor);
        }
    }
}

/// <summary>
/// �Փˏ������s����ǉ�
/// </summary>
/// <param name="conflictProccesor">�ǉ��������Փˏ������s��</param>
/// <param name="hitChecker">�Ăт�����̓����蔻��</param>
void ConflictManager::AddConflictProcessor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    processorKeyMap.insert(std::make_pair(conflictProcessor, hitChecker));
    hitCheckerKeyMap.insert(std::make_pair(hitChecker, conflictProcessor));
    AddHitChecker(hitChecker);
}

/// <summary>
/// �Փˏ������s�����폜
/// </summary>
/// <param name="conflictProccesor">���������Փˏ������s��</param>
/// /// <param name="hitChecker">�����蔻�������</param>
void ConflictManager::EraceConflictProccesor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    if (!processorKeyMap.empty())
    {
        //�Փˏ������s����map����폜
        for (auto mapItr = processorKeyMap.begin(); mapItr != processorKeyMap.end(); mapItr++)
        {
            if ((*mapItr).first == conflictProcessor)
            {
                processorKeyMap.erase(mapItr);
                break;
            }
        }
        //�����蔻�肪Key��map����폜
        for (auto mapItr = hitCheckerKeyMap.begin(); mapItr != hitCheckerKeyMap.end(); mapItr++)
        {
            if ((*mapItr).first == hitChecker)
            {
                hitCheckerKeyMap.erase(mapItr);
                break;
            }
        }
        //�����蔻��폜
        EraceHitChecker(hitChecker);
    }
}
/// <summary>
/// �f�o�b�O�p�̋������蔻���������
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = hitCheckList.begin(); objIte != hitCheckList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}
/// <summary>
/// �����̃I�u�W�F�N�g���m���Ԃ����Ă��邩���ׂ��̌��ʂ�Ԃ�
/// </summary>
/// <param name="conflictProccesor">�Փˏ������s��</param>
/// <param name="hitChecker">�����蔻��</param>
/// <returns>�Փˌ���</returns>
ConflictExamineResultInfo ConflictManager::GetConflictResultInfo(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker)
{
    HitCheckExamineObjectInfo examineInfo = conflictProccesor->GetHitExamineCheckInfo();
    //�����̃I�u�W�F�N�g���̂��̂Ɠ������Ă���X���[ ���������ĂȂ��Ă��Ԃ����Ă��邩���ׂȂ�
    if (hitChecker != processorKeyMap[conflictProccesor] && !hitChecker->IsDead())
    {
        //�������Ă��邩���ׂ�
        ConflictExamineResultInfo examineResultInfo = hitChecker->HitCheck(examineInfo);

        //������������n��
        return examineResultInfo;
    }
    return ConflictExamineResultInfo{};
}

/// <summary>
/// �����蔻�������
/// </summary>
void ConflictManager::Update()
{
    //�Փˏ������s��
    for (auto processorItr = processorKeyMap.begin(); processorItr != processorKeyMap.end(); processorItr++)
    {
        //�����蔻�蒲����
        for (auto hitCheckItr = hitCheckList.begin(); hitCheckItr != hitCheckList.end(); hitCheckItr++)
        {
            //�����蔻�茋��
            ConflictExamineResultInfo resultInfo = GetConflictResultInfo((*processorItr).first, *hitCheckItr);
            //�Փˏ������s�𓯎m�̏Փ˂Ȃ�
            if (hitCheckerKeyMap.contains(*hitCheckItr))
            {
                //�������ɂ������蔻�菈�����s
                hitCheckerKeyMap[*hitCheckItr]->ConflictProcess(GetConflictResultInfo(hitCheckerKeyMap[*hitCheckItr], processorKeyMap[(*processorItr).first]));
            }
            //�Փˏ������s
            (*processorItr).first->ConflictProcess(resultInfo);
        }
    }
}
