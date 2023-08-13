#pragma once
#include "ObjectObserver.h"
class PlayerCar;
/// <summary>
/// プレイヤーの情報を渡すやつ
/// </summary>
class PlayerObserver :public ObjectObserver
{
public:
    /// <summary>
    /// プレイヤーの情報を渡すやつ
    /// </summary>
    /// <param name="playerCar">プレイヤー</param>
    PlayerObserver(PlayerCar* playerCar);
    /// <summary>
    /// 収集アイテムを所得した回数
    /// </summary>
    /// <returns></returns>
    int GetCollectCount();
private:
    //プレイヤー
    PlayerCar* subject;
};