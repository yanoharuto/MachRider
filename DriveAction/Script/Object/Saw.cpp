#include "Saw.h"
#include "InitObjKind.h"
#include "OriginalMath.h"
#include "SphereHitChecker.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
//��]��
const float Saw::addRotate = 20.0f;
/// <summary>
/// ��]�̂�����
/// </summary>
/// <param name="arrangementData">�z�u���</param>
Saw::Saw(PlacementData arrangementData)
    :Actor(saw)
{
    //�����蔻��
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor,collider);
    
    //�j�󎞂̃G�t�F�N�g
    EffectManager::LoadEffect(bombExplosion);
    //����������
    Init(arrangementData);
}
/// <summary>
/// �p������Ȃ炱����
/// </summary>
Saw::Saw(ObjectInit::InitObjKind kind, PlacementData arrangementData)
    :Actor(kind)
{
    Init(arrangementData);
}
/// <summary>
/// �����蔻�����
/// </summary>
Saw::~Saw()
{
    ConflictManager::EraceConflictProccesor(conflictProcessor,collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(conflictProcessor);
    
    StopEffekseer3DEffect(breakExplosionEffect);
}
/// <summary>
/// ��]����
/// </summary>
void Saw::Update()
{
    direction = VNorm(OriginalMath::GetYRotateVector(direction,addRotate));
    //�j��G�t�F�N�g���o����I��
    if (breakExplosionEffect != -1 && IsEffekseer3DEffectPlaying(breakExplosionEffect) == -1)
    {
        objState = dead;
    }
    //�Փ˒���A�����蔻��폜
    if (objState == activeEnd && collider != nullptr)
    {
        ConflictManager::EraceConflictProccesor(conflictProcessor, collider);
        SAFE_DELETE(collider);
        SAFE_DELETE(conflictProcessor);
    }
}
/// <summary>
/// �Փˏ������s player�ɂԂ�������j��
/// </summary>
void Saw::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == player && objState != activeEnd)
    {
        objState = activeEnd;
        //���j�G�t�F�N�g���o��
        breakExplosionEffect = EffectManager::GetPlayEffect3D(bombExplosion);
        SetPosPlayingEffekseer3DEffect(breakExplosionEffect, position.x, position.y, position.z);
    }
}
/// <summary>
/// ����������
/// </summary>
/// <param name="arrangementData">�z�u���</param>
void Saw::Init(PlacementData arrangementData)
{
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    tag = damageObject;
    direction = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
}
