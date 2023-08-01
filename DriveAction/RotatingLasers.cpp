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
//�ŏ��̉�]����
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// ������
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(InitParam setParam, std::unique_ptr<ObjectObserver> setObserver)
    :DamageObject(setParam.initKind, std::move(setObserver))
{
    //�����ƃG�t�F�N�g
    EffectManager::LoadEffect(laserTrack);
    direction = setObserver->GetSubjectDir();
    //�����蔻��
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
/// ���[�U�[��y����]
/// </summary>
/// <param name="rotaSpeed"></param>
/// <param name="laserRange"></param>
void RotatingLasers::YRotate(float rotaSpeed, float laserRange)
{
    position = observer->GetSubjectPos();
    //�����ύX�@�G�t�F�N�g�̌�����ς���
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction) * RAGE;
    //���[�U�[�̏I���_
    endPos = VAdd(position, VScale(direction, position.y * laserRange));
    endPos.y = 0;
    //�G�t�F�N�g�I�������������񌂂�
    if (laserEffect == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(laserKind);
    }
    //�G�t�F�N�g�̌����Ƃ��ꏊ���C��
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    if (VCross(VGet(1, 0, 0), direction).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, -effectRota, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    }
    //�n�ʂɃ��[�U�[�ՃG�t�F�N�g
    SetLaserTrack();
}
/// <summary>
/// ���[�U�[���������ꏊ�Ɍ���o��
/// </summary>
void RotatingLasers::SetLaserTrack()
{
    //���[�U�[�Ղ̃G�t�F�N�g���\�����I������
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(laserTrack);
    }
    SetPosPlayingEffekseer3DEffect(trackEffect, endPos.x, 0, endPos.z);
}