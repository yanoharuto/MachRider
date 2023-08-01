#include "BigRadiusLaser.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h "
#include "ObjectObserver.h"
const InitParam BigRadiusLaser::initParam =
{
    ObjectInit::InitObjKind::bigRadiusLaser,
    1.333f
};
//回転速度
const float BigRadiusLaser::rotaSpeed = 2.0f;
/// <summary>
/// y軸回転する半径が大きいレーザー
/// </summary>
/// <param name="setObserver"></param>
BigRadiusLaser::BigRadiusLaser(std::unique_ptr<ObjectObserver> setObserver)
    :RotatingLasers(initParam, std::move(setObserver))
{
    laserKind = bigRadiusLaserEffect;
    EffectManager::LoadEffect(laserKind);
}

/// <summary>
/// y軸回転する
/// </summary>
void BigRadiusLaser::Update()
{
    if (observer->GetSubjectState()== active)
    {
        //エフェクト終了したらもう一回撃つ
        if (laserEffect == -1)
        {
            laserEffect = EffectManager::GetPlayEffect3D(laserKind);
        }
        //y軸回転
        YRotate(rotaSpeed, initParam.laserRange);
        //position = observer->GetSubjectPos();
        ////エフェクトの向きとか場所を修正
        //SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
        //SetLaserTrack();
    }
}
