#include "Item.h"

/// <summary>
/// �g���ĂȂ���Ԃɂ���
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
/// �A�C�e���̌��ʔ���
/// </summary>
void ItemBase::ShowEffect(ItemArgumentCarInfo carInfo)
{
    if (useSituation != ItemUseSituation::DoneUsing)
    {
        useSituation = ItemUseSituation::Useing;
    }
}
/// <summary>
/// �A�C�e���̏���n��
/// </summary>
/// <returns>�A�C�e���̌��ʗʁA���g���邩�A�A�C�e���̎�ށA�A�C�e���̎g�p��</returns>
ItemInfo ItemBase::GetItemInfo()
{
    ItemInfo info;
    info.effecacyValue = effecacyValue;

    info.itemTag = itemTag;
    info.itemSituation = useSituation;
    return info;
}
