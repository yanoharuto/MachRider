#pragma once
#include <string>
#include "DamageObject.h"
#include "EffectManager.h"
class LaserCollider;
class ObjectObserver;
struct InitParam
{
    ObjectInit::InitObjKind initKind;
    float laserSize;
    float trackSize;
    float radius;
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
    RotatingLasers(InitParam setParam, ObjectObserver* setObserver);
    ~RotatingLasers()override;
    /// <summary>
    /// レーザーの回転
    /// </summary>
    /// <param name="rotaSpeed"></param>
    /// <param name="laserRange"></param>
    void YRotate(float rotaSpeed, float laserRange);
    /// <summary>
    /// レーザー跡を出す
    /// </summary>
    void SetLaserTrack();
protected:
    EffectInit::EffectKind laserKind;
    //エフェクトハンドル
    int laserEffect = -1;
    //焼き後
    int trackEffect = -1;
    //エフェクトのシャドウになるカプセルを描画したか
    bool isDrawShadow = false;
    //エフェクトの回転角（ラジアン）
    float effectRota;
    //最初の回転方向
    static const VECTOR firstDir;
    //レーザーの跡の位置
    VECTOR endPos = {};
    //線状当たり判定
    LaserCollider* collider;
};