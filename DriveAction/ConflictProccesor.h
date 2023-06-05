#pragma once
#include <list>
#include <unordered_map>
#include "Timer.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// �����蔻����s��
/// </summary>
class  ConflictProccesor abstract
{
public:
    /// <summary>
    /// �Փˌ�̏��������Ȃ��Ă����Ȃ�f�t�H���g�R���X�g���N�^
    /// </summary>
    ConflictProccesor() {};
    /// <summary>
    /// �Փˌ�̏���������Ȃ炱����
    /// </summary>
    /// <param name="obj"></param>
    ConflictProccesor(Actor* obj);

    virtual ~ConflictProccesor();
    /// <summary>
    /// �����蔻����s��
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    virtual ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) = 0;
    /// <summary>
    /// �����蔻��ŕK�v�ȏ���n��
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo();
    /// <summary>
    /// �����蔻��̏������Ăяo��
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo);
    /// <summary>
    /// �����蔻��œ���̂��̂ɃN�[���^�C������������ꍇ�^�C�}�[���Z�b�g�o����
    /// </summary>
    /// <param name="tag">����̎҂̃^�O</param>
    /// <param name="timer">�N�[���^�C���v���p�̃^�C�}�[</param>
    void SetCoolTimer(Object::ObjectTag tag,float setCoolTime);
    /// <summary>
    /// �����̃^�O�̃I�u�W�F�N�g�ɉ���Ԃ��������Ԃ�
    /// </summary>
    /// <param name="objTag"></param>
    /// <returns></returns>
    int GetTagHitCount(Object::ObjectTag objTag);
protected:
    /// <summary>
    /// �����̃I�u�W�F�N�g�̓��������񐔂𑝂₷
    /// </summary>
    /// <param name="objTag"></param>
    void IncrementHitCount(Object::ObjectTag objTag);
    //�����蔻��̎�����
    Actor* object = nullptr;
    //�N�[���^�C�}�[
    std::unordered_map<Object::ObjectTag, Timer*> coolTimer;
    //�Ԃ������^�O�̓��������񐔂��L�^
    std::unordered_map<Object::ObjectTag, int> hitCountMap;
};