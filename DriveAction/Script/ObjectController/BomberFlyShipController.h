#pragma once
#include "FlyShipController.h"
/// <summary>
/// 爆撃機管理クラス
/// </summary>
class BomberFlyShipController : public FlyShipController
{
public:
    /// <summary>
    /// 爆撃機の管理の初期化
    /// </summary>
    BomberFlyShipController();
    /// <summary>
    /// 爆撃機を追加する
    /// </summary>
    /// <param name="editData">配置情報</param>
    void AddObject(PlacementData editData)override;
};

