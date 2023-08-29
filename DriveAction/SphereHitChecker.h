#pragma once
#include "Object.h"
struct HitCheckInfo;
struct CollisionResultInfo;
class Actor;
/// <summary>
/// �����m�̓����蔻������܂�
/// </summary>
class SphereHitChecker
{
public:
    /// <summary>
    /// �����m�̓����蔻����s��
    /// </summary>
    /// <param name="obj">�����蔻��̎�����</param>
    SphereHitChecker(Actor* const obj);
    ~SphereHitChecker();
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objA">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objB">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(Object* const objA, Object* const objB);
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objA">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(Object* const objA, const HitCheckInfo objBInfo);
    /// <summary>
    /// �����������ǂ������ׂ��
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA<</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheck(const HitCheckInfo objAInfo, const HitCheckInfo objBInfo);

    /// <summary>
    /// �����蔻����s��
    /// </summary>
    /// <param name="hitCheckInfo">���̌��ʓ����������ʒu������邩</param>
    /// <returns></returns>
    virtual CollisionResultInfo HitCheck(HitCheckInfo hitCheckInfo) = 0;

    /// <summary>
    /// �����蔻��ŏՓ˂��Ă��邩���ׂ�̂ɕK�v�ȏ���n��
    /// </summary>
    /// <returns></returns>
    virtual HitCheckInfo GetHitExamineCheckInfo()const;

    /// <summary>
    /// true�Ȃ瓖���蔻�薳��
    /// </summary>
    /// <returns></returns>
    bool IsDead();
protected:
    /// <summary>
    /// �����������ǂ������ׂ�Ƃ��̋��ʏ���
    /// </summary>
    /// <param name="objAInfo">���ׂ����I�u�W�F�N�gA</param>
    /// <param name="objBInfo">���ׂ����I�u�W�F�N�gB</param>
    /// <returns>����������True</returns>
    bool HitCheckProcess(HitCheckInfo objAInfo, HitCheckInfo objBInfo);

    //�����蔻��̎�����
    Actor* object = nullptr;
};

