#pragma once
#include <list>
#include <unordered_map>
class ConflictProcessor;
class SphereHitChecker;
struct CollisionResultInfo;
/// <summary>
///  �����蔻���Z�߂čs�����߂̓z
/// </summary>
class ConflictManager
{
public:
    /// <summary>
    /// �����蔻���Z�߂čs�����߂̓z
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
    /// <param name="conflictProcessor">�Փˏ������Ă�ConflictProcessor��ǉ�</param>
    /// <param name="hitChecker">conflictProcessor�̓����蔻��</param>
    static void AddConflictProcessor(ConflictProcessor* const conflictProcessor,SphereHitChecker* const hitChecker);
    /// <summary>
    /// �Փˏ������s�����폜
    /// </summary>
    /// <param name="conflictProcessor">���������Փˏ������s��</param>
    /// /// <param name="hitChecker">�����蔻�������</param>
    static void EraceConflictProcessor(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker);
    /// <summary>
    /// �f�o�b�O�p�����o��
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// �����Փ˂��Ă��镨���Ȃ������ׂ�
    /// </summary>
    void Update();
private:

    /// <summary>
    /// �����̃I�u�W�F�N�g���m���Ԃ����Ă��邩���ׂ��̌��ʂ�Ԃ�
    /// </summary>
    /// <param name="conflictProcessor">�Փˏ������s��</param>
    /// <param name="hitChecker">�����蔻��</param>
    /// <returns>�Փˌ���</returns>
    CollisionResultInfo GetConflictResultInfo(ConflictProcessor* const conflictProcessor, SphereHitChecker* const hitChecker);
    //�����������ʂ𔽉f������N���X�̃}�b�v
    static std::unordered_map<ConflictProcessor*, SphereHitChecker*> processorKeyMap;
    //conflictProcessor�����̓����蔻�肩���ׂ邽�߂̃}�b�v
    static std::unordered_map<SphereHitChecker*, ConflictProcessor*> hitCheckerKeyMap;
    //�������Ă��邩���ׂ�N���X�̃��X�g
    static std::list<SphereHitChecker*> hitCheckList;
};