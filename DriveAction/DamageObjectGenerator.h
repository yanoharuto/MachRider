#pragma once
#include <list>
#include "ItemTag.h"
class ObjectSubject;
class DamageObject;
class ActorController;
class ActorControllerManager;
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
class DamageObjectGenerator
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    DamageObjectGenerator();
    ~DamageObjectGenerator();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">発射した人の情報を渡す</param>
    /// <returns></returns>
    static void GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub);

    void GetObjectList(ActorControllerManager* controllerManager);
private:
    static std::list<ActorController*> createDamageObject;
};