#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "InitObjKind.h"
#include "SphereCollider.h"
#include "ObjectObserver.h"
//落下速度
 const float Rocket::setFallingSpeed = 0.7f;
//重力
 const float Rocket::gravityPower = 0.08f;
 //燃えた時の当たり判定の大きさ
 const float Rocket::setBurnRadius = 42.0f;
Rocket::Rocket(ObjectObserver* setObserver)
    :DamageObject(ObjectInit::bomber,setObserver)
{
    position = observer->GetSubPos();
    fallingSpeed = setFallingSpeed;
    tag = ObjectTag::damageObject;
    EffectManager::LoadEffect(bombExplosion);
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    onGround = false;
    collider = new SphereCollider(this);
}
/// <summary>
/// 球当たり判定
/// </summary>
Rocket::~Rocket()
{
    StopEffekseer3DEffect(burnEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(observer);
}
/// <summary>
/// 更新
/// </summary>
/// <param name="deltaTime"></param>
void Rocket::Update()
{
    //地面にぶつかる前は落ちていく
    if (!onGround)
    {
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //地面にぶつかりそうになかったらエフェクトを出す
        if (position.y < 0.0f)
        {
            if (burnEffect == -1)
            {
                burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
                float positionY = position.y - radius;
                SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
                radius = setBurnRadius;
                onGround = true;
            }
        }
    }
    else
    {
        //エフェクトを描画し終わったら終了
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            aliveFlag = false;
            burnEffect = -1;
        }
    }
    UpdatePosition();
}
/// <summary>
/// 衝突後の処理
/// </summary>
void Rocket::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject)
    {
        if (burnEffect==-1)
        {
            //ダメージ判定のあるオブジェクト以外に衝突後エフェクトを出す
            burnEffect = EffectManager::GetPlayEffect3D(bombExplosion);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
            //当たり判定を爆発と同じくらいにする
            radius = setBurnRadius;
            onGround = true;
        }
    }
}