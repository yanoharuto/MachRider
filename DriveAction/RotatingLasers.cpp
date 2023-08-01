#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "Timer.h"
#include "LaserCollider.h"
#include "ObjectObserver.h"
//最初の回転方向
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// 初期化
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(InitParam setParam, std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(setParam.initKind, std::move(setObserver))
{
    //向きとエフェクト
    EffectManager::LoadEffect(laserTrack);
    direction = setObserver->GetSubjectDir();
    //当たり判定
    collider = new LaserCollider(this,setParam.laserRange);
    ConflictManager::AddHitChecker(collider);
}

RotatingLasers::~RotatingLasers()
{
    StopEffekseer3DEffect(laserEffect);
    laserEffect = -2;
    StopEffekseer3DEffect(trackEffect);
    trackEffect = -2;
    ConflictManager::EraceHitChecker(collider);
    SAFE_DELETE(collider);
    observer.reset();
}
/// <summary>
/// レーザーのy軸回転
/// </summary>
/// <param name="rotaSpeed"></param>
/// <param name="laserRange"></param>
void RotatingLasers::YRotate(float rotaSpeed, float laserRange)
{
    position = observer->GetSubjectPos();
    //方向変更　エフェクトの向きを変える
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction) * RAGE;
    //レーザーの終着点
    endPos = VAdd(position, VScale(direction, position.y * laserRange));
    endPos.y = 0;
    //エフェクト終了したらもう一回撃つ
    if (laserEffect == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(laserKind);
    }
    //エフェクトの向きとか場所を修正
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    if (VCross(VGet(1, 0, 0), direction).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, -effectRota, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    }
    //地面にレーザー跡エフェクト
    SetLaserTrack();
}
/// <summary>
/// レーザーを撃った場所に後を出す
/// </summary>
void RotatingLasers::SetLaserTrack()
{
    //レーザー跡のエフェクトが表示し終えたら
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(laserTrack);
    }
    SetPosPlayingEffekseer3DEffect(trackEffect, endPos.x, 0, endPos.z);
}