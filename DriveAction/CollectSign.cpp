#include "CollectSign.h"
#include "UIManager.h"
#include "CollectController.h"
#include "PlayerObserver.h"
#include "DxLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "Utility.h"

/// <summary>
/// 収集アイテムの方向を記すエフェクトを出す
/// </summary>
CollectSign::CollectSign(std::weak_ptr<PlayerObserver> player)
{
    playerObserver = player;
    EffectManager::LoadEffect(compass);
}
/// <summary>
/// エフェクト終了
/// </summary>
CollectSign::~CollectSign()
{
    StopEffekseer3DEffect(signEffect);
}
/// <summary>
/// エフェクトの位置と向きを設定
/// </summary>
void CollectSign::Update()
{
    //今収集アイテムが動いているか
    if (CollectController::IsActiveCollect())
    {
        //エフェクトが止まってたらもう一度再生
        if (IsEffekseer3DEffectPlaying(signEffect) == -1)
        {
            signEffect = EffectManager::GetPlayEffect3D(EffectInit::compass);
        }
        //エフェクトはプレイヤーの足元に表示
        VECTOR pos = playerObserver.lock()->GetSubjectPos();
        pos.y += addYPos;
        SetPosPlayingEffekseer3DEffect(signEffect, pos.x, pos.y, pos.z);
        //方向を収集アイテムの方向に設定
        float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), CollectController::GetBetween(pos));
        if (VCross(VGet(1, 0, 0), CollectController::GetBetween(pos)).y < 0)
        {
            SetRotationPlayingEffekseer3DEffect(signEffect, 0, -degree * RAGE, 0);
        }
        else
        {
            SetRotationPlayingEffekseer3DEffect(signEffect, 0, degree * RAGE, 0);
        }
    }
    else
    {
        //動いてない間は停止
        StopEffekseer3DEffect(signEffect);
    }
}