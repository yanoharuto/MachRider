#pragma once
#include <string>
#include "DamageObject.h"
#include "EffectManager.h"
class LaserCollider;
class ObjectObserver;
struct InitParam
{
    ObjectInit::InitObjKind initKind;
    float laserRange;
};
/// <summary>
/// ��]���[�U�[
/// </summary>
class RotatingLasers abstract :public DamageObject
{
public:
    /// <summary>
    /// ��]���[�U�[
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(InitParam setParam, std::unique_ptr<ObjectObserver> setObserver);
    ~RotatingLasers()override;
    /// <summary>
    /// ���[�U�[��y����]
    /// </summary>
    /// <param name="rotaSpeed"></param>
    /// <param name="laserRange"></param>
    void YRotate(float rotaSpeed, float laserRange);
    /// <summary>
    /// ���[�U�[�Ղ��o��
    /// </summary>
    void SetLaserTrack();
protected:
    //���[�U�[�̎��
    EffectInit::EffectKind laserKind;
    //�G�t�F�N�g�n���h��
    int laserEffect = -1;
    //�Ă���
    int trackEffect = -1;
    //�G�t�F�N�g�̉�]�p�i���W�A���j
    float effectRota;
    //�ŏ��̉�]����
    static const VECTOR firstDir;
    //���[�U�[�̐Ղ̈ʒu
    VECTOR endPos = {};
    //���󓖂��蔻��
    LaserCollider* collider;
    float radius = 20.0f;
};