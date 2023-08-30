#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
using namespace ObjectInit;
class SphereHitChecker;
class ConflictProcessor;
/// <summary>
/// ��Q���@�i�ۂ̂��j
/// </summary>
class Saw :
    public Actor
{
public:
    /// <summary>
    /// �����̏ꏊ�ɐݒu����
    /// </summary>
    /// <param name="arrangementData">�ҏW�f�[�^</param>
    Saw(PlacementData arrangementData);
    /// <summary>
    /// MoveSaw�Ȃǌp������Ȃ�
    /// </summary>
    /// <param name="kind">�p����̎��</param>
    /// <param name="arrangementData">�z�u���</param>
    Saw(ObjectInit::InitObjKind kind, PlacementData arrangementData);
    /// <summary>
    /// �����蔻�����
    /// </summary>
    ~Saw();
    /// <summary>
    /// ��]������
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update() override;
    /// <summary>
    /// �Փˏ������s player�ɂԂ�������j��
    /// </summary>
    void OnConflict(const CollisionResultInfo conflictInfo) override;
    
protected:
    /// <summary>
    /// ����������
    /// </summary>
    /// <param name="arrangementData">�z�u���</param>
    void Init(PlacementData arrangementData);
    //��]��
    static const float addRotate;
    //�����蔻��
    SphereHitChecker* collider;
    //�Փˏ������s��
    ConflictProcessor* conflictProcessor;
    //�j�󔚔j�G�t�F�N�g
    int breakExplosionEffect = -1;
};