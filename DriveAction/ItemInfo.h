#pragma once
#include "ItemTag.h"
#include "ItemUseSituation.h"
/// <summary>
/// �A�C�e���̌���
/// </summary>
struct  ItemInfo
{
    //�A�C�e�����ʗ�
    float effecacyValue;
    //�A�C�e�����g���Ă�����
    bool isFiriable;
    //�A�C�e���̎��
    Item::ItemTag itemTag;
    //�A�C�e���̏�
    ItemUseSituation itemSituation;
};