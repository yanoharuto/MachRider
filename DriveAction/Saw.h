#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "EditObjectData.h"
#include "InitObjKind.h"
using namespace ObjectInit;
class SphereCollider;
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
    Saw(EditArrangementData arrangementData);
    /// <summary>
    /// �p������Ȃ炱����
    /// </summary>
    Saw(ObjectInit::InitObjKind kind, EditArrangementData arrangementData);
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
    void ConflictProcess(const ConflictExamineResultInfo conflictInfo) override;
    
protected:
    /// <summary>
    /// ���ʏ���������
    /// </summary>
    /// <param name="arrangementData"></param>
    void Init(EditArrangementData arrangementData);
    //��]��
    static const float addRotate;
    //�����蔻��
    SphereCollider* collider;
    //�Փˏ������s��
    ConflictProcessor* conflictProcessor;
    //�j�󔚔j�G�t�F�N�g
    int breakExplosionEffect = -1;
};