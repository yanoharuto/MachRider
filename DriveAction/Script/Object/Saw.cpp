#include "Saw.h"
#include "InitObjKind.h"
#include "OriginalMath.h"
#include "SphereHitChecker.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "ConflictProcessor.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
//回転量
const float Saw::addRotate = 20.0f;
/// <summary>
/// 回転のこぎり
/// </summary>
/// <param name="arrangementData">配置情報</param>
Saw::Saw(PlacementData arrangementData)
    :Actor(InitObjKind::saw)
{
    //当たり判定
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor,collider);
    
    //破壊時のエフェクト
    EffectManager::LoadEffect(EffectKind::bombExplosion);
    //初期化処理
    Init(arrangementData);
}
/// <summary>
/// 継承するならこっち
/// </summary>
Saw::Saw(ObjectInit::InitObjKind kind, PlacementData arrangementData)
    :Actor(kind)
{
    Init(arrangementData);
}
/// <summary>
/// 当たり判定消去
/// </summary>
Saw::~Saw()
{
    ConflictManager::EraceConflictProcessor(conflictProcessor,collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(conflictProcessor);
    
    StopEffekseer3DEffect(breakExplosionEffect);
}
/// <summary>
/// 回転する
/// </summary>
void Saw::Update()
{
    direction = VNorm(OriginalMath::GetYRotateVector(direction,addRotate));
    //破壊エフェクトが出たら終了
    if (breakExplosionEffect != -1 && IsEffekseer3DEffectPlaying(breakExplosionEffect) == -1)
    {
        objState = ObjectState::dead;
    }
    //衝突直後、当たり判定削除
    if (objState == ObjectState::activeEnd && collider != nullptr)
    {
        ConflictManager::EraceConflictProcessor(conflictProcessor, collider);
        SAFE_DELETE(collider);
        SAFE_DELETE(conflictProcessor);
    }
}
/// <summary>
/// 衝突処理実行 playerにぶつかったら破壊
/// </summary>
void Saw::OnConflict(const CollisionResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::player && objState != ObjectState::activeEnd)
    {
        objState = ObjectState::activeEnd;
        //爆破エフェクトを出す
        breakExplosionEffect = EffectManager::GetPlayEffect3D(EffectKind::bombExplosion);
        SetPosPlayingEffekseer3DEffect(breakExplosionEffect, position.x, position.y, position.z);
    }
}
/// <summary>
/// 初期化処理
/// </summary>
/// <param name="arrangementData">配置情報</param>
void Saw::Init(PlacementData arrangementData)
{
    position.x = arrangementData.posX;
    position.z = arrangementData.posZ;
    tag = ObjectTag::damageObject;
    direction = VGet(arrangementData.dirX, 0, arrangementData.dirZ);
}
