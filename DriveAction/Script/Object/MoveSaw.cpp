#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "AddMoveSawDataLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereHitChecker.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// �ړ���]�̂�����
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(PlacementData editData)
    :Saw(InitObjKind::moveSaw,editData)
{   
    //�ǉ���񂩂�ړ����x�Ȃǂ�����
    auto addDataLoader = new AddMoveSawDataLoader();
    auto addStrDataVec = addDataLoader->GetLoadData();
    using enum MoveParametor;
    //�^�C�}�[�������Ă���Ԃ�������
    moveLarpTimer = new ReusableTimer(STR_TO_D(addStrDataVec[CAST_I(moveTime)]));
    //�O�������ɓ���
    velocity = VScale(direction, STR_TO_F(addStrDataVec[CAST_I(moveSpeed)]));
    //�����蔻��
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
    //�j�󎞂̃G�t�F�N�g
    EffectManager::LoadEffect(EffectKind::bombExplosion);
}
/// <summary>
/// �ړ����Ȃ����]����
/// </summary>
void MoveSaw::Update()
{
    if (moveLarpTimer->IsOverLimitTime())//���Ԃ����ς��������甽�Ε����ɓ���
    {
        moveLarpTimer->Reuse();//�ړ����Ԃ����Z�b�g
        
        velocity = VSub(VGet(0,0,0),velocity);//�ړ��������]
    }
    position = VAdd(position, velocity);
    //��]
    Saw::Update();
}