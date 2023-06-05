#pragma once
#include <list>
#include <unordered_map>
#include "ConflictProccesor.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
/// <summary>
/// �����蔻���Z�߂Ă��邽�߂̓z
/// </summary>
class ConflictManager
{
public:
    ConflictManager();
    ~ConflictManager();
    /// <summary>
    /// �Ԃ����Ă邩���ׂ������ǉ�����
    /// </summary>
    /// <param name="obj"></param>
    static void AddConflictObjInfo(ConflictProccesor* conflictProccesor);
    /// <summary>
    /// �����蔻�����������
    /// </summary>
    /// <param name="conflictProccesor"></param>
    static void EraceConflictObjInfo(ConflictProccesor* conflictProccesor);
    /// <summary>
    /// �f�o�b�O�p�����o��
    /// </summary>
    void DrawCollisionSphere();
    /// <summary>
    /// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    std::list<ConflictExamineResultInfo> GetConflictObjInfo(ConflictProccesor* conflictProccesor);
    void Update();
private:

    static std::list<ConflictProccesor*> conflictObjList;
};