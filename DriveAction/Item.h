#pragma once
#include "DxLib.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
#include "ItemUseSituation.h"
#include "Actor.h"
#include "ItemInfo.h"
#include "Timer.h"
/// <summary>
/// アイテムの基底クラス
/// </summary>
class ItemBase abstract:Actor
{
public:
    /// <summary>
    /// アイテムの基底クラス
    /// </summary>
    ItemBase();
    virtual ~ItemBase();
    /// <summary>
    /// アイテムの更新
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="carInfo"></param>
    virtual void Update(ItemArgumentCarInfo carInfo) = 0;
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw();
    /// <summary>
    /// アイテムの効果発揮
    /// </summary>
    virtual void ShowEffect(ItemArgumentCarInfo carInfo);
    /// <summary>
    /// アイテムの情報
    /// </summary>
    /// <returns></returns>
    ItemInfo GetItemInfo();
protected:
    //アイテムの効果量
    float effecacyValue;
    //アイテムの効果時間
    float effecacyTime = 0;
    //描画モデル
    int modelHandle;
    //アイテムを使っている状態かどうか
    ItemUseSituation useSituation;
    //アイテムの種類を教えて
    Item::ItemTag itemTag;
};