#pragma once
#include "RotatingLasers.h"
class ObjectObserver;
/// <summary>
/// y軸回転するレーザー
/// </summary>
class BigRadiusLaser:public RotatingLasers
{
public:
    /// <summary>
    /// y軸回転する半径が大きいレーザー
    /// </summary>
    /// <param name="setObserver"></param>
    BigRadiusLaser(std::unique_ptr<ObjectObserver> setObserver);

    /// <summary>
    /// y軸回転させる
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;

private:
    //レーザーエフェクトのパス
    static const InitParam initParam;
    
    //回転速度
    static const float rotaSpeed;
};

