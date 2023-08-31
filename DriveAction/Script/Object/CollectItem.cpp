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
//回転量
const float Coin::rotateY = 2.5f;
//コサインで使う
const float Coin::moveYValue = 0.2f;
//Y移動速度
const float Coin::moveYSpeed = 4.0f;

/// <summary>
/// 初期化
/// </summary>
/// <param name="arrangementData"></param>
Coin::Coin(PlacementData arrangementData)
    :Actor(ObjectInit::collect)
{
    //位置
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    firstY = position.y;
    //エフェクトと音
    SoundPlayer::LoadSound(coinGet);
    EffectManager::LoadEffect(getCollect);
    EffectManager::LoadEffect(collectAura);
    tag = ObjectTag::collect;
    //当たり判定
    conflictProcessor = new ConflictProcessor(this);
    collider = new SphereHitChecker(this);
}

Coin::~Coin()
{
    if (collider != nullptr)//当たり判定消去
    {
        ConflictManager::EraceConflictProccesor(conflictProcessor, collider);
        SAFE_DELETE(conflictProcessor);
        SAFE_DELETE(collider); 
    }
    //エフェクト終了
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
/// くるくる回転
/// </summary>
void Coin::Update()
{
    if (objState == sleep)//初めて動くとき当たり判定を付ける
    {
        ConflictManager::AddConflictProcessor(conflictProcessor, collider);
        objState = active;
    }
    //上下に回転しながら移動
    MoveAndRotate();
    //車にぶつかってたら当たり判定を削除
    if (isCarConflict == true)
    {
        if (conflictProcessor != nullptr)
        {
            ConflictManager::EraceConflictProccesor(conflictProcessor, collider);
            SAFE_DELETE(conflictProcessor);
            SAFE_DELETE(collider);
        }
        //効果音がなり終わって終了
        if(!SoundPlayer::IsPlaySound(coinGet))
        {
            objState = dead;
        }
    }
    //コインの出すオーラが途切れたら再開させる
    if (IsEffekseer3DEffectPlaying(coinAuraEffect) == -1)
    {
        coinAuraEffect = EffectManager::GetPlayEffect3D(collectAura);
        SetPosPlayingEffekseer3DEffect(coinAuraEffect, position.x, position.y - radius, position.z);
    }
    //Velocityを反映
    ReflectsVelocity();
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void Coin::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player)
    {
       //エフェクトと音を出す
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
/// 上下に回転しながら移動
/// </summary>
void Coin::MoveAndRotate()
{
    //向きを変更
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //ちょっと上下に動く
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
}
