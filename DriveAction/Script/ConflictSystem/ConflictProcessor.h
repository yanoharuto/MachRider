#pragma once
#include <unordered_map>
#include <list>
struct CollisionResultInfo;
struct HitCheckInfo;
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
    /// <summary>
    /// ���ɂȂ�
    /// </summary>
    virtual ~ConflictProcessor() {};
    /// <summary>
    /// �����蔻��̏������Ăяo��
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void OnConflict(CollisionResultInfo resultInfo);

    /// <summary>
    /// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;
protected:
    /// <summary>
    /// �����蔻��̎�����
    /// </summary>
    Actor* object = nullptr;
};