#include "LittleRadiusLaser.h"
#include "EffectManager.h"
//回転速度
const float LittleRadiusLaser::rotaSpeed = 4.0f;
//レーザーの中心からの距離
const InitParam LittleRadiusLaser::initParam =
{

    ObjectInit::InitObjKind::littleRadiusLaser,
    120.0f,
    30.0f,
    20.0f,
    0.325f,
};
LittleRadiusLaser::LittleRadiusLaser(ObjectObserver* setObserver)
    :RotatingLasers(initParam, setObserver)
{
    laserKind = littleRadiusLaserEffect;
    EffectManager::LoadEffect(laserKind);
}


void LittleRadiusLaser::Update()
{
    RotateLaser(rotaSpeed,initParam.laserRange);
    SetLaserTrack();
}
