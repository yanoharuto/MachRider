#pragma once
#include <list>
class AddableObjectController;
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
/// <summary>
/// actorの動きを制御している物を全部束ねて動かす
/// </summary>
class ActorControllerManager final
{
public:
    /// <summary>
    /// 敵などをNewして配置する
    /// </summary>
    ActorControllerManager();
    /// <summary>
    /// 敵の管理クラスやステージのオブジェクトなどをすべて解放
    /// </summary>
    ~ActorControllerManager();
    /// <summary>
    /// 更新
    /// </summary>
    void Update();
    /// <summary>
    /// ゲーム開始前更新
    /// </summary>
    void PrepareGame();
    /// <summary>
    /// 各アクターの描画
    /// </summary>
    void Draw()const;
    /// <summary>
    /// actor管理クラスを追加
    /// </summary>
    /// <param name="actorController">actor管理クラス</param>
    void AddActorController(ActorController* actorController);
private:
    /// <summary>
    /// 2つのActor管理クラスどちらでも使えるゲーム開始前更新
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void PrepareGame(std::list<controllerClass*> controllerList);
    /// <summary>
    /// 2つのActor管理クラスどちらでも使える更新
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void Update(std::list<controllerClass*> controllerList);
    /// <summary>
    /// 2つのActor管理クラスどちらでも使える描画
    /// </summary>
    /// <typeparam name="controllerClass">Actor管理クラス</typeparam>
    /// <param name="controllerList">controllerClassを纏めたリスト</param>
    template<typename controllerClass>
    void Draw(std::list<controllerClass*> controllerList)const;
    /// <summary>
    ///　敵生成処理
    /// </summary>
    void GenerateEnemyProcess();
    //収集アイテムの数
    int collectNum = 0;
    //actor管理クラスのリスト
    std::list<ActorController*> actorControllerList;
    //追加可能クラスActor管理クラスのリスト
    std::list<AddableObjectController*> addableActorControllerList;
    //敵が発射してきたりしたアイテムを作成
    DamageObjectGenerator* damageObjGenerator;
    //収集アイテムが回収されると増える敵を作成する
    EnemyGenerator* enemyGenerator;
};