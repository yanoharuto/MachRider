#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "Timer.h"
#include "LineCollider.h"
#include "ObjectObserver.h"
//最初の回転方向
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// 初期化
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(InitParam setParam, ObjectObserver* setObserver)
    :DamageObject(setParam.initKind, setObserver)
{
    tag = ObjectTag::damageObject;
    
    EffectManager::LoadEffect(laserTrack);
    direction = firstDir;
    radius = setParam.radius;
    collider = new LineCollider(this,setParam.laserRange);

}

RotatingLasers::~RotatingLasers()
{
    StopEffekseer3DEffect(laserEffect);
    laserEffect = -2;
    StopEffekseer3DEffect(trackEffect);
    trackEffect = -2;
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
    SAFE_DELETE(observer);
}

void RotatingLasers::YRotate(float rotaSpeed, float laserRange)
{
    position = observer->GetSubjectPos();
    //方向変更　エフェクトの向きを変える
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota -= rotaSpeed * RAGE;
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
    SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    //地面にレーザー跡エフェクト
    SetLaserTrack();
    isDrawShadow = false;
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