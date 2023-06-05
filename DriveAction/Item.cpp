#include "Item.h"

/// <summary>
/// 使ってない状態にする
/// </summary>
ItemBase::ItemBase()
{
    useSituation = ItemUseSituation::nonUse;
    effecacyValue = {};
}

ItemBase::~ItemBase()
{
}
void ItemBase::Draw()
{
    MV1DrawModel(modelHandle);
}
/// <summary>
/// アイテムの効果発揮
/// </summary>
void ItemBase::ShowEffect(ItemArgumentCarInfo carInfo)
{
    if (useSituation != ItemUseSituation::DoneUsing)
    {
        useSituation = ItemUseSituation::Useing;
    }
}
/// <summary>
/// アイテムの情報を渡す
/// </summary>
/// <returns>アイテムの効果量、今使えるか、アイテムの種類、アイテムの使用状況</returns>
ItemInfo ItemBase::GetItemInfo()
{
    ItemInfo info;
    info.effecacyValue = effecacyValue;

    info.itemTag = itemTag;
    info.itemSituation = useSituation;
    return info;
}
