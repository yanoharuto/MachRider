#pragma once
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
class Actor;
class DrawModel;
class CameraObserver;
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
    /// <summary>
    /// 描画役とオブジェクトのデリート
    /// </summary>
    virtual ~ActorController();
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update();
    /// <summary>
    /// ゲーム開始準備処理
    /// </summary>
    virtual void PrepareGame();
    /// <summary>
    /// 描画処理
    /// </summary>
    virtual void Draw(std::weak_ptr<CameraObserver> cameraObserever)const;
protected:
    /// <summary>
    /// 描画役とActorListの解放
    /// </summary>
    void DeleteActorListAndDrawModel();
    //このリストを回す
    std::list<Actor*> actorList;
    //描画担当
    DrawModel* drawModel = nullptr;
    //操作するオブジェクトの種類
    ObjectInit::InitObjKind controllObjKind;
};