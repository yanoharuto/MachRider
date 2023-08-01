#pragma once
#include <list>
#include <unordered_map>
class ConflictProcessor;
class SphereHitChecker;
struct ConflictExamineResultInfo;
/// <summary>
/// �����蔻���Z�߂Ă��邽�߂̓z
/// </summary>
class ConflictManager
{
public:
    /// <summary>
    /// �����蔻���Z�߂Ă��邽�߂̓z
    /// </summary>
    ConflictManager();
    ~ConflictManager();
    /// <summary>
    /// �����蔻��ǉ�
    /// </summary>
    /// <param name="hitChecker"></param>
    static void AddHitChecker(SphereHitChecker* hitChecker);
    /// <summary>
    /// �����蔻�����
    /// </summary>
    /// <param name="hitChecker"></param>
    static void EraceHitChecker(SphereHitChecker* hitChecker);
    /// <summary>
    /// �Փˏ������Ăт������ǉ�
    /// </summary>
    /// <param name="conflictProccesor">�Ăт������</param>
    /// <param name="hitChecker">�Ăт�����̓����蔻��</param>
    static void AddConflictProcessor(ConflictProcessor* conflictProccesor,SphereHitChecker* hitChecker);

    /// <summary>
    /// �Փˏ������Ă΂Ȃ��Ă����悤�ɂ���
    /// </summary>
    /// <param name="conflictProccesor">�Ă΂Ȃ��Ă����悤��</param>
    static void EraceConflictProccesor(ConflictProcessor* conflictProccesor, SphereHitChecker* hitChecker);
    /// <summary>
    /// �f�o�b�O�p�����o��
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// �����̃I�u�W�F�N�g���m���Ԃ����Ă��邩���ׂ��̌��ʂ�Ԃ�
    /// </summary>
    /// <param name="conflictProccesor">�Փˏ������s��</param>
    /// <param name="hitChecker">�����蔻��</param>
    /// <returns>�Փˌ���</returns>
    ConflictExamineResultInfo GetConflictResultInfo(ConflictProcessor* conflictProccesor, SphereHitChecker* hitChecker);
    /// <summary>
    /// �����Փ˂��Ă��镨���Ȃ������ׂ�
    /// </summary>
    void Update();
private:
    //�����������ʂ𔽉f������N���X�̃}�b�v
    static std::unordered_map<ConflictProcessor*, SphereHitChecker*> processorKeyMap;
    
    static std::unordered_map<SphereHitChecker*, ConflictProcessor*> hitCheckerKeyMap;
    //�������Ă��邩���ׂ�N���X�̃��X�g
    static std::list<SphereHitChecker*> hitCheckList;
};