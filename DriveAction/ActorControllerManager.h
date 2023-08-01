#pragma once
#include <list>
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
class ActorControllerManager final
{
public:
    ActorControllerManager();
    ~ActorControllerManager();
    /// <summary>
    /// 更新
    /// </summary>
    void Update();
    /// <summary>
    /// ゲーム開始前更新
    /// </summary>
    void GameReserve();
    /// <summary>
    /// 各アクターの描画
    /// </summary>
    void Draw()const;
    /// <summary>
    /// actor管理クラスを追加
    /// </summary>
    /// <param name="actorController"></param>
    void AddActorController(ActorController* actorController);
private:
    /// <summary>
    ///　敵生成処理
    /// </summary>
    void GenerateEnemyProcess();
    //収集アイテムの数
    int collectNum = 0;
    //actor管理クラスのリスト
    static std::list<ActorController*> actorControllerList;
    //敵が発射してきたりしたアイテムを作成
    DamageObjectGenerator* damageObjGenerator;
    //収集アイテムが回収されると増える敵を作成する
    EnemyGenerator* enemyGenerator;
};

