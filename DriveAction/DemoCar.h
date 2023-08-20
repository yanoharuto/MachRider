#pragma once
#include "Car.h"
/// <summary>
/// タイトル画面で走らせる車
/// </summary>
class DemoCar :
    public Car
{
public:
    /// <summary>
    /// 位置などの初期化とエフェクトのロード
    /// </summary>
    /// <param name="setPos">初期位置</param>
    /// <param name="setDir">初期向き</param>
    DemoCar(VECTOR setPos,VECTOR setDir);
    /// <summary>
    /// タイヤとエフェクト削除
    /// </summary>
    ~DemoCar()override;
    /// <summary>
    /// 初期位置に戻す
    /// </summary>
    void InitPosition();
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
private:
    /// <summary>
    /// エフェクトの更新
    /// </summary>
    void EffectUpdate();
    /// <summary>
    /// 走る速さベクトルの所得
    /// </summary>
    /// <returns></returns>
    void UpdateAccelPower()override;
    //走るエフェクト
    int runEffect = -1;
    //初期位置
    VECTOR firstPos;
    //初期向き
    VECTOR firstDir;
    //加速度
    const float setAcceleSpeed = 2;
    //最大値
    const float setMaxSpeed = 5;
};

