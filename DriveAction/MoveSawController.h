#pragma once
#include "ActorController.h"
/// <summary>
/// 移動する回転のこぎりの管理者
/// </summary>
class MoveSawController :
    public ActorController
{
public:
    /// <summary>
    /// 移動する回転のこぎりの管理者
    /// </summary>
    MoveSawController();
    /// <summary>
    /// 移動する回転のこぎりの追加
    /// </summary>
    /// <param name="editData"></param>
    void AddObject(std::vector<EditArrangementData> editData)override;
    /// <summary>
    /// 更新。　破壊されたら破棄
    /// </summary>
    void Update()override;
};

