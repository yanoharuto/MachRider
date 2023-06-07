#include "LittleRadiusLaser.h"
#include "EffectManager.h"
#include "ObjectObserver.h"

//��]���x
const float LittleRadiusLaser::rotaSpeed = 4.0f;
//���[�U�[�̒��S����̋���
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
    if (observer->GetSubjectState() == alive)
    {
        RotateLaser(rotaSpeed, initParam.laserRange);
        SetLaserTrack();
    }
}
