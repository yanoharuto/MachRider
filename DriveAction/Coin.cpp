#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
//��]��
const float Coin::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float Coin::moveYValue = 0.2f;
//Y�ړ����x
const float Coin::moveYSpeed = 4.0f;
//���a
const float Coin ::setRadius = 46.0f;
//����y���W
const float Coin::firstY = 23.0f; 

/// <summary>
/// ������
/// </summary>
/// <param name="firstPos"></param>
Coin::Coin(VECTOR firstPos)
    :Actor(ObjectInit::collect)
{
    position = firstPos;
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
    radius = setRadius;
    SoundPlayer::LoadSound(coinGet);
    EffectManager::LoadEffect(getCoin);
    tag = ObjectTag::coin;
    firstPos.y += radius;
}

Coin::~Coin()
{
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// ���邭���]
/// </summary>
void Coin::Update()
{
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
            aliveFlag = false;
        }
    }
    UpdatePosition();
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
       coinPlayEffect = EffectManager::GetPlayEffect2D(getCoin);
       int effectX = SCREEN_WIDTH / 2;
       int effectY = SCREEN_HEIGHT / 2;
       int success = SetPosPlayingEffekseer2DEffect(coinPlayEffect,effectX, effectY, 5);
       SoundPlayer::Play3DSE(coinGet);
       isCarConflict = true;
    }
}

void Coin::Draw() const
{/*
    VECTOR lightDir = GetLightDirection();
    VECTOR lightPos = position;
    lightPos.y += 300;
    ChangeLightTypeSpot(lightPos, VGet(0, -1.0f, 0), DX_PI_F / 2, DX_PI_F / 4, 2000.0f, 0.0f, 0.008f, 0.0f);*/

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    if (modelHandle != -1)
    {
        ModelSetMatrix();
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, position);
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
    }
    //�s������ɖ߂�
    MV1SetRotationMatrix(modelHandle, tmpMat);

   // ChangeLightTypeDir(lightDir);
}