#pragma once
#include <list>
class Player;
class ObjectSubject;
/// <summary>
/// 車乗りのマネージャー
/// </summary>
class RacerManager
{
public:
    RacerManager() {};
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="lacerNum">車乗りの数だけリストに追加するよ</param>
    /// <returns></returns>
    RacerManager(int cpuNum);
    //デストラクタ
    ~RacerManager();
    /// <summary>
    /// 車乗りたちの更新
    /// </summary>
    /// <param name="deltaTime">フレーム間の経過時間</param>
    /// <param name="circuit">走るコース</param>
    void RacerUpdate();
    /// <summary>
    /// 上下に動かす
    /// </summary>
    void UpDown();
    /// <summary>
    /// 描画
    /// </summary>
    /// <returns></returns>
    void Draw();
    ObjectSubject* GetPlayerSubject(int num);
private:
    Player* CreatePlayer();
    std::list<Player*> racerList;
};