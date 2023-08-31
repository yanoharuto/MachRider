#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// 上下に移動する飛行艇
/// </summary>
class UpDownFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// 上下に移動する飛行艇の初期化
    /// </summary>
    UpDownFlyShipController();
protected:
    /// <summary>
    /// 追加する
    /// </summary>
    /// <param name="editData">配置する位置や向き</param>
    void AddObject(PlacementData editData)override;
};

