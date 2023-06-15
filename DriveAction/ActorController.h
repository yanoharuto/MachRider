#pragma once
#include <list>
class Actor;
/// <summary>
/// 1つの種類のactorの子クラスを動かすために使う
/// </summary>
class ActorController
{
public:
    ActorController();
    ActorController(Actor* actor);
    virtual ~ActorController();
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update();
    /// <summary>
    /// ゲーム開始準備処理
    /// </summary>
    virtual void GameReserve() {};
    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw()const;
    /// <summary>
    /// 役割を終えてたらfalse
    /// </summary>
    /// <returns></returns>
    virtual bool IsAlive()const;
protected:
    //このリストを回す
    std::list<Actor*> actorList;
};

