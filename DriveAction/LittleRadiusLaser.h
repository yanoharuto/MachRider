#pragma once
#include "RotatingLasers.h"

/// <summary>
/// 軸回転する半径が小さいレーザー
/// </summary>
class LittleRadiusLaser :
    public RotatingLasers
{
public:
    /// <summary>
/// 軸回転する半径が小さいレーザー
/// </summary>
    LittleRadiusLaser(std::unique_ptr<ObjectObserver> observer);
    /// <summary>
    /// 回転
    /// </summary>
    void Update()override;
private:
    /// 回転速度
    static const float rotaSpeed;
    
    /// 初期化情報
    static const InitParam initParam;
};

