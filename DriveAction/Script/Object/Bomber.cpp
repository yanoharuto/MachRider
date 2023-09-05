#include "Bomber.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "SphereHitChecker.h"
#include "ConflictProcessor.h"
#include "ObjectObserver.h"
//落下速度
 const float Bomber::setFallingSpeed = 0.3f;
//重力
 const float Bomber::gravityPower = 0.1f;
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
Bomber::Bomber(std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(ObjectInit::bomber,std::move(setObserver))
{
    //落下位置は発射したキャラの位置に準拠
    position = observer->GetSubjectPos();
    //初速をセット
    fallingSpeed = setFallingSpeed;
    //エフェクト
    EffectManager::LoadEffect(bombExplosion);
    //向きと速度
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    //当たり判定
    collider = new SphereHitChecker(this);
    conflictProcessor = new ConflictProcessor(this);
    ConflictManager::AddConflictProcessor(conflictProcessor, collider);
}
/// <summary>
/// 球当たり判定削除
/// </summary>
Bomber::~Bomber()
{
    //当たり判定削除
    EraceCollider();
    StopEffekseer3DEffect(burnEffect);
    observer.reset();
}
/// <summary>
/// 更新
/// </summary>
/// <param name="deltaTime"></param>
void Bomber::Update()
{
    //地面にぶつかる前は落ちていく
    if (burnEffect == -1)
    {
        //だんだん加速しながら落ちていく
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //地面にぶつかりそうになかったらエフェクトを出す
        if (position.y < 0.0f)
        {
            burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        }
    }
    else
    {
        //エフェクトを描画し終わったら終了
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            objState = dead;
        }
    }
}
/// <summary>
/// 衝突後の処理
/// </summary>
void Bomber::OnConflict(CollisionResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject && burnEffect == -1)
    {
        //ダメージ判定のあるオブジェクト以外に衝突後エフェクトを出す
        burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
        float positionY = position.y - radius;
        SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
        //当たったのがプレイヤーだったら当たり判定消失
        if (resultInfo.tag == player)
        {
            objState = activeEnd;
        }
    }
}
/// <summary>
/// 当たり判定削除
/// </summary>
void Bomber::EraceCollider()
{
    if (collider != nullptr)
    {
        ConflictManager::EraceConflictProcessor(conflictProcessor, collider);
        SAFE_DELETE(collider);
        SAFE_DELETE(conflictProcessor);
    }
}
