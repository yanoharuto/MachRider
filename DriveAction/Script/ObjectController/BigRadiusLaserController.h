#pragma once
#include "DamageObjectController.h"
#include <vector>
class ObjectObserver;
/// <summary>
/// y軸回転する大回りするレーザー
/// </summary>
class BigRadiusLaserController : public DamageObjectController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    BigRadiusLaserController();
    /// <summary>
    /// レーザーを照射したオブジェクトを引数にもらう
    /// </summary>
    /// <param name="sub">レーザーを照射したオブジェクト</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
};

