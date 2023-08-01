#pragma once
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
class Actor;
class ModelViewer;
/// <summary>
/// 1つの種類のactorの子クラスを動かすために使う
/// </summary>
class ActorController abstract
{
public:
    /// <summary>
    /// 操作するオブジェクトの名前を下さい
    /// </summary>
    ActorController(ObjectInit::InitObjKind kind) { controllObjKind = kind; };
    virtual ~ActorController();
    /// <summary>
    /// リストに追加
    /// </summary>
    /// <param name="editData"></param>
    virtual void AddObject(std::vector<EditArrangementData> editData) {};
    /// <summary>
    /// 操作しているオブジェクトの種類
    /// </summary>
    /// <returns></returns>
    virtual ObjectInit::InitObjKind GetControllObjKind() { return controllObjKind; };
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update();
    /// <summary>
    /// ゲーム開始準備処理
    /// </summary>
    virtual void GameReserve();
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
    //描画担当
    ModelViewer* viewer = nullptr;
    //操作するオブジェクトの種類
    ObjectInit::InitObjKind controllObjKind;
};