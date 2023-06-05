#pragma once
#include "RotatingLasers.h"
class ObjectObserver;

class BigRadiusLaser:public RotatingLasers
{
public:
    BigRadiusLaser(ObjectObserver* setObserver);

    /// <summary>
/// 回転させる
/// </summary>
/// <param name="deltaTime"></param>
    void Update()override;

private:
    //レーザーエフェクトのパス
    static const InitParam initParam;
    
    //回転速度
    static const float rotaSpeed;
};

