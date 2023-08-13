#include "MoveSaw.h"
#include "ReusableTimer.h"
#include "CSVFileLoader.h"
#include "InitActor.h"
#include "OriginalMath.h"
#include "SphereCollider.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// �ړ���]�̂�����
/// </summary>
/// <param name="editData"></param>
MoveSaw::MoveSaw(EditArrangementData editData)
    :Saw(moveSaw,editData)
{   
    //�ǉ���񂩂�ړ����x�Ȃǂ�����
    auto addDataLoader = new CSVFileLoader(InitActor::GetAddDataPass(moveSaw));
    auto addStrDataVec = addDataLoader->GetLoadStringData();
    //�^�C�}�[�������Ă���Ԃ�������
    moveLarpTimer = new ReusableTimer(atoi(addStrDataVec[moveTime].c_str()));
    //�O�������ɓ���
    velocity = VScale(direction, atoi(addStrDataVec[moveSpeed].c_str()));
    //�����蔻��
    collider = new SphereCollider(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
    //�j�󎞂̃G�t�F�N�g
    EffectManager::LoadEffect(bombExplosion);
    
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