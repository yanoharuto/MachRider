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
    120.0f,
    30.0f,
    20.0f,
    1.3f
};
//‰ñ“]‘¬“x
const float BigRadiusLaser::rotaSpeed = 2.0f;

BigRadiusLaser::BigRadiusLaser(ObjectObserver* setObserver)
    :RotatingLasers(initParam, setObserver)
{
    laserKind = bigRadiusLaserEffect;
    EffectManager::LoadEffect(laserKind);
}


void BigRadiusLaser::Update()
{
    if (observer->GetSubjectState()== active)
    {
        YRotate(rotaSpeed, initParam.laserRange);
        SetLaserTrack();
    }
}
