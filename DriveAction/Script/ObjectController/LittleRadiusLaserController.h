#pragma once
#include <vector>
#include "DamageObjectController.h"
class ObjectObserver;
/// <summary>
/// 小さくy軸回転するレーザーの更新役
/// </summary>
class LittleRadiusLaserController : public DamageObjectController
{
public:
    /// <summary>
    /// 小さくy軸回転するレーザーの更新役
    /// </summary>
    LittleRadiusLaserController();
    /// <summary>
    /// レーザーを照射したオブジェクトを引数にもらう
    /// </summary>
    /// <param name="sub">レーザーを照射したオブジェクト</param>
    void OnGenerateDamageObject(std::unique_ptr<ObjectObserver> sub)override;
};