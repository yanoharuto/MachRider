#include "CollectItem.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
#include "InitActor.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
//��]��
const float Coin::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float Coin::moveYValue = 0.2f;
//Y�ړ����x
const float Coin::moveYSpeed = 4.0f;

/// <summary>
/// ������
/// </summary>
/// <param name="arrangementData"></param>
Coin::Coin(PlacementData arrangementData)
    :Actor(ObjectInit::collect)
{
    //�ʒu
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    firstY = position.y;
    //�G�t�F�N�g�Ɖ�
    SoundPlayer::LoadSound(coinGet);
    EffectManager::LoadEffect(getCollect);
    EffectManager::LoadEffect(collectAura);
    tag = ObjectTag::collect;
    //�����蔻��
    conflictProcessor = new ConflictProcessor(this);
    collider = new SphereHitChecker(this);
}

Coin::~Coin()
{
    if (collider != nullptr)//�����蔻�����
    {
        ConflictManager::EraceConflictProccesor(conflictProcessor, collider);
        SAFE_DELETE(conflictProcessor);
        SAFE_DELETE(collider); 
    }
    //�G�t�F�N�g�I��
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) != -1)
    {
        StopEffekseer3DEffect(coinAuraEffect);
    }
    if (IsEffekseer3DEffectPlaying(coinGetEffect) != -1)
    {
        StopEffekseer3DEffect(coinGetEffect);
    }
}
/// <summary>
/// ���邭���]
/// </summary>
void Coin::Update()
{
    if (objState == sleep)//���߂ē����Ƃ������蔻���t����
    {
        ConflictManager::AddConflictProcessor(conflictProcessor, collider);
        objState = active;
    }
    //�㉺�ɉ�]���Ȃ���ړ�
    MoveAndRotate();
    //�ԂɂԂ����Ă��瓖���蔻����폜
    if (isCarConflict == true)
    {
        if (conflictProcessor != nullptr)
        {
            ConflictManager::EraceConflictProccesor(conflictProcessor, collider);
            SAFE_DELETE(conflictProcessor);
            SAFE_DELETE(collider);
        }
        //���ʉ����Ȃ�I����ďI��
        if(!SoundPlayer::IsPlaySound(coinGet))
        {
            objState = dead;
        }
    }
    //�R�C���̏o���I�[�����r�؂ꂽ��ĊJ������
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y - radius, position.z);
    }
    //Velocity�𔽉f
    ReflectsVelocity();
}
/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void Coin::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player)
    {
       //�G�t�F�N�g�Ɖ����o��
       coinGetEffect = EffectManager::GetPlayEffect2D(getCollect);
       float effectX = SCREEN_WIDTH / 2;
       float effectY = SCREEN_HEIGHT / 2;
       SetPosPlayingEffekseer2DEffect(coinGetEffect,effectX, effectY, 5);
       SoundPlayer::Play3DSE(coinGet);
       isCarConflict = true;
       objState = activeEnd;
    }
}
/// <summary>
/// �㉺�ɉ�]���Ȃ���ړ�
/// </summary>
void Coin::MoveAndRotate()
{
    //������ύX
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //������Ə㉺�ɓ���
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
}
