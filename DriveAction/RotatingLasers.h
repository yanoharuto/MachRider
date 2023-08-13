#pragma once
#include <string>
#include "DamageObject.h"
#include "EffectManager.h"
class LaserCollider;
class ObjectObserver;
//レーザーの初期化に必要
struct InitParam
{
    ObjectInit::InitObjKind initKind;
    //高さ1に対するレーザーの射程
    float laserRange;
};
/// <summary>
/// 回転レーザー
/// </summary>
class RotatingLasers abstract :public DamageObject
{
public:
    /// <summary>
    /// 回転レーザー
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(InitParam setParam, std::unique_ptr<ObjectObserver> setObserver);
    ~RotatingLasers()override;
    /// <summary>
    /// レーザーのy軸回転
    /// </summary>
    /// <param name="rotaSpeed"></param>
    /// <param name="laserRange"></param>
    void YRotate(float rotaSpeed, float laserRange);
    /// <summary>
    /// レーザー跡を出す
    /// </summary>
    void SetLaserTrack();
protected:
    //レーザーの種類
    EffectInit::EffectKind laserKind;
    //エフェクトハンドル
    int laserEffect = -1;
    //焼き後
    int trackEffect = -1;
    //エフェクトの回転角（ラジアン）
    float effectRota;
    //レーザーの跡の位置
    VECTOR endPos = {};
    //線状当たり判定
    LaserCollider* collider;
    float radius = 20.0f;
};