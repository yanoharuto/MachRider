#pragma once
#include "ActorController.h"
/// <summary>
/// プレイヤーをはじき飛ばす丸鋸
/// </summary>
class SawController :
    public ActorController
{
public:
    /// <summary>
    /// プレイヤーをはじき飛ばす丸鋸
    /// </summary>
    SawController();
    /// <summary>
/// 丸鋸を追加
/// </summary>
/// <param name="editData">追加する位置などの情報</param>
    void AddObject(std::vector<EditArrangementData> editData)override;
    void Update()override;
};

