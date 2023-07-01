#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
#include "InitActor.h"
//��]��
const float Coin::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float Coin::moveYValue = 0.2f;
//Y�ړ����x
const float Coin::moveYSpeed = 4.0f;

/// <summary>
/// ������
/// </summary>
/// <param name="firstPos"></param>
Coin::Coin(VECTOR firstPos)
    :Actor(ObjectInit::collect)
{
    firstPos.y = 0;
    position = VAdd(position,firstPos);
    collider = nullptr;
    firstY = position.y;
    SoundPlayer::LoadSound(coinGet);
    EffectManager::LoadEffect(getCollect);
    EffectManager::LoadEffect(collectAura);
    tag = ObjectTag::collect;
}

Coin::~Coin()
{
    if (collider != nullptr)
    {
        ConflictManager::EraceConflictObjInfo(collider);
        SAFE_DELETE(collider);
    }
}
/// <summary>
/// ���邭���]
/// </summary>
void Coin::Update()
{
    if (objState == sleep)//���߂ē����Ƃ������蔻���t����
    {
        collider = new SphereCollider(this);
        objState = active;
    }
    //������ύX
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //������Ə㉺�ɓ���
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
    //�ԂɂԂ����Ă�����ʉ����o���ďI��
    if (isCarConflict == true)
    {
        ConflictManager::EraceConflictObjInfo(collider);
        SAFE_DELETE(collider);
        if(!SoundPlayer::IsPlaySound(coinGet))
        {
            objState = dead;
        }
    }
    //�R�C���̏o���I�[�����r�؂ꂽ��ĊJ������
    if (!IsEffekseer3DEffectPlaying(coinAuraEffect) || coinAuraEffect == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y, position.z);
    }
    ReflectsVelocity();
}
/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="conflictInfo"></param>
void Coin::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player)
    {
       //�G�t�F�N�g�Ɖ����o��
       coinGetEffect = EffectManager::GetPlayEffect2D(getCollect);
       int effectX = SCREEN_WIDTH / 2;
       int effectY = SCREEN_HEIGHT / 2;
       SetPosPlayingEffekseer2DEffect(coinGetEffect,effectX, effectY, 5);
       SoundPlayer::Play3DSE(coinGet);
       isCarConflict = true;
       objState = activeEnd;
    }
}
/// <summary>
/// �Q�[���J�n�O�̍X�V
/// </summary>
void Coin::GameReserve()
{
    Update();
}
