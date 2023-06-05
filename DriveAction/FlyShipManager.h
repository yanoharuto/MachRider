#pragma once
#include <list>
#include <unordered_map>
#include "ObjectObserver.h"
class Timer;
class FlyShipCommander;
class RacerManager;
/// <summary>
/// 敵機のマネージャー
/// </summary>
class FlyShipManager
{
public:
    /// <summary>
    /// 敵機の初期化する
    /// </summary>
    FlyShipManager(RacerManager* racerManager);

    ~FlyShipManager();
    /// <summary>
    /// 敵機たちの更新
    /// </summary>
    /// <param name="infoCenter"></param>
    void Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //敵機のマップ
    std::unordered_map<int, std::list<FlyShipCommander*>> commanderMap;
    //爆撃機再利用のタイマー
    Timer* bomberFlyShipGoTimer;
    //プレイヤーの位置
    ObjectObserver* playerObserver;
};