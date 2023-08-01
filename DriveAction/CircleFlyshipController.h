#pragma once
#include "FlyShipController.h"
#include "EditObjectData.h"
/// <summary>
/// 輪になっているレーザー照射機の更新とかする
/// </summary>
class CircleFlyShipController:
    public FlyShipController
{
public:
    /// <summary>
/// 輪になっているレーザー照射機の更新とかする
/// </summary>
    CircleFlyShipController();
    /// <summary>
    /// 輪になっているレーザー照射機の追加
    /// </summary>
    void AddObject(std::vector<EditArrangementData> arrangementData) override;
private:
    /// <summary>
/// 輪になっているレーザー照射機の配置と追加
/// </summary>
    void AddObject(EditArrangementData arrangementData);
};

