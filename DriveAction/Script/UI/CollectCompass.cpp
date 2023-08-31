#include "CollectCompass.h"
#include "UIManager.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"
/// <summary>
/// エフェクトの読みこみ
/// </summary>
/// <param name="player">プレイヤーの位置などを貰うことが出来るオブザーバー</param>
CollectCompass::CollectCompass(std::weak_ptr<PlayerObserver> player)
{
    playerObserver = player;
    EffectManager::LoadEffect(compass);
}
/// <summary>
/// エフェクト終了
/// </summary>
CollectCompass::~CollectCompass()
{
    StopEffekseer3DEffect(compassEffect);
}
/// <summary>
/// エフェクトの位置と向きを設定
/// </summary>
void CollectCompass::Update()
{
    //今収集アイテムが動いているか
    if (CollectController::IsActiveCollect())
    {
        //エフェクトが止まってたらもう一度再生
        if (IsEffekseer3DEffectPlaying(compassEffect) == -1)
        {
            compassEffect = EffectManager::GetPlayEffect3D(EffectInit::compass);
        }
        //エフェクトはプレイヤーの足元に表示
        VECTOR pos = playerObserver.lock()->GetSubjectPos();
        pos.y += addYPos;
        SetPosPlayingEffekseer3DEffect(compassEffect, pos.x, pos.y, pos.z);
        //方向を収集アイテムの方向に設定
        float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), CollectController::GetCollectItemBetween(pos));
        if (VCross(VGet(1, 0, 0), CollectController::GetCollectItemBetween(pos)).y < 0)
        {
            SetRotationPlayingEffekseer3DEffect(compassEffect, 0, -degree * RAGE, 0);
        }
        else
        {
            SetRotationPlayingEffekseer3DEffect(compassEffect, 0, degree * RAGE, 0);
        }
    }
    else
    {
        //動いてない間は停止
        StopEffekseer3DEffect(compassEffect);
    }
}