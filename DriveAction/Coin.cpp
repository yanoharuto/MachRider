#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
//回転量
const float Coin::rotateY = 2.5f;
//コサインで使う
const float Coin::moveYValue = 0.2f;
//Y移動速度
const float Coin::moveYSpeed = 4.0f;
//半径
const float Coin ::setRadius = 46.0f;
//初期y座標
const float Coin::firstY = 23.0f; 

/// <summary>
/// 初期化
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
    EffectManager::LoadEffect(coinAura);
    tag = ObjectTag::coin;
    firstPos.y += radius;
}

Coin::~Coin()
{
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// くるくる回転
/// </summary>
void Coin::Update()
{
    //向きを変更
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //ちょっと上下に動く
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
    //車にぶつかってたら効果音を出して終了
    if (isCarConflict == true)
    {
        ConflictManager::EraceConflictObjInfo(collider);
        SAFE_DELETE(collider);
        if(!SoundPlayer::IsPlaySound(coinGet))
        {
            objState = dead;
        }
    }
    //コインの出すオーラが途切れたら再開させる
    if (!IsEffekseer3DEffectPlaying(coinAuraEffect) || coinAuraEffect == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(coinAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y, position.z);
    }
    UpdatePosition();
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void Coin::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player)
    {
       //エフェクトと音を出す
       coinGetEffect = EffectManager::GetPlayEffect2D(getCoin);
       int effectX = SCREEN_WIDTH / 2;
       int effectY = SCREEN_HEIGHT / 2;
       int success = SetPosPlayingEffekseer2DEffect(coinGetEffect,effectX, effectY, 5);
       SoundPlayer::Play3DSE(coinGet);
       isCarConflict = true;
    }
}

void Coin::Draw() const
{
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    if (modelHandle != -1)
    {
        ModelSetMatrix();
        // ３Dモデルのポジション設定
        MV1SetPosition(modelHandle, position);
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
    }
    //行列を元に戻す
    MV1SetRotationMatrix(modelHandle, tmpMat);

}