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
//�ŏ��̉�]����
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// ������
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
    //�����ύX�@�G�t�F�N�g�̌�����ς���
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota -= rotaSpeed * RAGE;
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
    SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
    //�n�ʂɃ��[�U�[�ՃG�t�F�N�g
    SetLaserTrack();
    isDrawShadow = false;
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