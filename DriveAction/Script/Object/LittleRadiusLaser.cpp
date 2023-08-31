#include "LittleRadiusLaser.h"
#include "EffectManager.h"
#include "ObjectObserver.h"
#include "EffekseerForDXLib.h"
//回転速度
const float LittleRadiusLaser::rotaSpeed = 2.0f;
//レーザーの中心からの距離
const InitParam LittleRadiusLaser::initParam =
{
    ObjectInit::InitObjKind::bigRadiusLaser,
    1.333f,
};

LittleRadiusLaser::LittleRadiusLaser(std::unique_ptr<ObjectObserver> setObserver)
    :RotatingLasers(initParam, std::move(setObserver))
{
    laserKind = bigRadiusLaserEffect;
    EffectManager::LoadEffect(laserKind);

}


void LittleRadiusLaser::Update()
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
    }
}