#pragma once
#include <unordered_map>
#include <list>
struct ConflictExamineResultInfo;
struct HitCheckExamineObjectInfo;
class Actor;
class SphereHitChecker;
/// <summary>
/// �Փˏ������s��
/// </summary>
class  ConflictProcessor
{
public:
    /// <summary>
    /// �Փˏ������s��
    /// </summary>
    /// <param name="obj">���s�������Փˏ���������I�u�W�F�N�g</param>
    ConflictProcessor(Actor* const obj);

    virtual ~ConflictProcessor() {};
    /// <summary>
    /// �����蔻��̏������Ăяo��
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void ConflictProcess(ConflictExamineResultInfo resultInfo);

    /// <summary>
/// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo()const;
protected:
    /// <summary>
    /// �����蔻��̎�����
    /// </summary>
    Actor* object = nullptr;
};