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
//��]���x
const float BigRadiusLaser::rotaSpeed = 2.0f;
/// <summary>
/// y����]���锼�a���傫�����[�U�[
/// </summary>
/// <param name="setObserver"></param>
BigRadiusLaser::BigRadiusLaser(std::unique_ptr<ObjectObserver> setObserver)
    :RotatingLasers(initParam, std::move(setObserver))
{
    laserKind = bigRadiusLaserEffect;
    EffectManager::LoadEffect(laserKind);
}

/// <summary>
/// y����]����
/// </summary>
void BigRadiusLaser::Update()
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
        //position = observer->GetSubjectPos();
        ////�G�t�F�N�g�̌����Ƃ��ꏊ���C��
        //SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
        //SetLaserTrack();
    }
}
