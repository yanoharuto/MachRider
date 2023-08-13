#include "LittleRadiusLaser.h"
#include "EffectManager.h"
#include "ObjectObserver.h"
#include "EffekseerForDXLib.h"
//��]���x
const float LittleRadiusLaser::rotaSpeed = 2.0f;
//���[�U�[�̒��S����̋���
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
        //�G�t�F�N�g�I�������������񌂂�
        if (laserEffect == -1)
        {
            laserEffect = EffectManager::GetPlayEffect3D(laserKind);
        }
        //y����]
        YRotate(rotaSpeed, initParam.laserRange);
    }
}