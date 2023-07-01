#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
#include "InitActor.h"
//回転量
const float Coin::rotateY = 2.5f;
//コサインで使う
const float Coin::moveYValue = 0.2f;
//Y移動速度
const float Coin::moveYSpeed = 4.0f;

/// <summary>
/// 初期化
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
/// くるくる回転
/// </summary>
void Coin::Update()
{
    if (objState == sleep)//初めて動くとき当たり判定を付ける
    {
        collider = new SphereCollider(this);
        objState = active;
    }
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
        coinAuraEffect = EffectManager::GetPlayEffect3D(collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y, position.z);
    }
    ReflectsVelocity();
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
/// ゲーム開始前の更新
/// </summary>
void Coin::GameReserve()
{
    Update();
}
