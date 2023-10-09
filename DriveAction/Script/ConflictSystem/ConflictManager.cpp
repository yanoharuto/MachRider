#include "ConflictManager.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ConflictProcessor.h"
#include "SphereHitChecker.h"
#include "Utility.h"
//�����������ʂ𔽉f������N���X�̃}�b�v
std::unordered_map<ConflictProcessor*,SphereHitChecker*> ConflictManager::processorKeyMap;
//conflictProcessor�����̓����蔻�肩���ׂ邽�߂̃}�b�v
std::unordered_map<SphereHitChecker*, ConflictProcessor*> ConflictManager::hitCheckerKeyMap;
//�������Ă��邩���ׂ�N���X�̃��X�g
std::list<SphereHitChecker*> ConflictManager::hitCheckList;
/// <summary>
/// �����蔻���Z�߂čs�����߂̓z
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
/// <param name="conflictProcessor">�ǉ��������Փˏ������s��</param>
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
/// <param name="conflictProcessor">���������Փˏ������s��</param>
/// /// <param name="hitChecker">�����蔻�������</param>
void ConflictManager::EraceConflictProcessor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
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
       HitCheckInfo info = (*objIte)->GetHitExamineCheckInfo();
       DrawSphere3D(info.pos, info.radius, 4, GetColor(Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE), GetColor(Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE, Utility::MAX1BYTEVALUE), false);
    }
}
/// <summary>
/// �����̃I�u�W�F�N�g���m���Ԃ����Ă��邩���ׂ��̌��ʂ�Ԃ�
/// </summary>
/// <param name="conflictProcessor">�Փˏ������s��</param>
/// <param name="hitChecker">�����蔻��</param>
/// <returns>�Փˌ���</returns>
CollisionResultInfo ConflictManager::GetConflictResultInfo(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker)
{
    HitCheckInfo examineInfo = conflictProcessor->GetHitExamineCheckInfo();
    //�����̃I�u�W�F�N�g���̂��̂Ɠ������Ă���X���[ ���������ĂȂ��Ă��Ԃ����Ă��邩���ׂȂ�
    if (hitChecker != processorKeyMap[conflictProcessor] && !hitChecker->IsDead())
    {
        //�������Ă��邩���ׂ�
        CollisionResultInfo examineResultInfo = hitChecker->HitCheck(examineInfo);

        //������������n��
        return examineResultInfo;
    }
    return CollisionResultInfo{};
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
            CollisionResultInfo resultInfo = GetConflictResultInfo((*processorItr).first, *hitCheckItr);
            //�Փˏ������s�𓯎m�̏Փ˂Ȃ�
            if (hitCheckerKeyMap.contains(*hitCheckItr))
            {
                //�������ɂ������蔻�菈�����s
                hitCheckerKeyMap[*hitCheckItr]->OnConflict(GetConflictResultInfo(hitCheckerKeyMap[*hitCheckItr], processorKeyMap[(*processorItr).first]));
            }
            //�Փˏ������s
            (*processorItr).first->OnConflict(resultInfo);
        }
    }
}
