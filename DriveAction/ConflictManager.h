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
    /// <summary>
    /// �����蔻��o�^Map�S����
    /// </summary>
    ~ConflictManager();
    /// <summary>
    /// �����蔻��ǉ�
    /// </summary>
    /// <param name="hitChecker"></param>
    static void AddHitChecker(SphereHitChecker* const hitChecker);
    /// <summary>
    /// �����蔻�����
    /// </summary>
    /// <param name="hitChecker"></param>
    static void EraceHitChecker(SphereHitChecker* const hitChecker);
    /// <summary>
    /// �Փˏ������Ă�ConflictProcessor��ǉ�
    /// </summary>
    /// <param name="conflictProccesor">�Փˏ������Ă�ConflictProcessor��ǉ�</param>
    /// <param name="hitChecker">conflictProcessor�̓����蔻��</param>
    static void AddConflictProcessor(ConflictProcessor* const conflictProccesor,SphereHitChecker* const hitChecker);
    /// <summary>
    /// �Փˏ������s�����폜
    /// </summary>
    /// <param name="conflictProccesor">���������Փˏ������s��</param>
    /// /// <param name="hitChecker">�����蔻�������</param>
    static void EraceConflictProccesor(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker);
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
    ConflictExamineResultInfo GetConflictResultInfo(ConflictProcessor* const conflictProccesor, SphereHitChecker* const hitChecker);
    /// <summary>
    /// �����Փ˂��Ă��镨���Ȃ������ׂ�
    /// </summary>
    void Update();
private:
    //�����������ʂ𔽉f������N���X�̃}�b�v
    static std::unordered_map<ConflictProcessor*, SphereHitChecker*> processorKeyMap;
    //conflictProcessor�����̓����蔻�肩���ׂ邽�߂̃}�b�v
    static std::unordered_map<SphereHitChecker*, ConflictProcessor*> hitCheckerKeyMap;
    //�������Ă��邩���ׂ�N���X�̃��X�g
    static std::list<SphereHitChecker*> hitCheckList;
};