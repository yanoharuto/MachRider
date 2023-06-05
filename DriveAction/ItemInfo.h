#pragma once
#include "ItemTag.h"
#include "ItemUseSituation.h"
/// <summary>
/// アイテムの効果
/// </summary>
struct  ItemInfo
{
    //アイテム効果量
    float effecacyValue;
    //アイテムを使っていいか
    bool isFiriable;
    //アイテムの種類
    Item::ItemTag itemTag;
    //アイテムの状況
    ItemUseSituation itemSituation;
};