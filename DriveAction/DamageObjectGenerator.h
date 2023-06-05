#pragma once
#include <string>
#include "ItemTag.h"
class ObjectSubject;
class DamageObject;
class ObjectObserver;
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
    /// アイテムの種類によって生成するアイテムを変更する
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static DamageObject* GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub);
};