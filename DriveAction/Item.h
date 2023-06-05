#pragma once
#include "DxLib.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
#include "ItemUseSituation.h"
#include "Actor.h"
#include "ItemInfo.h"
#include "Timer.h"
/// <summary>
/// �A�C�e���̊��N���X
/// </summary>
class ItemBase abstract:Actor
{
public:
    /// <summary>
    /// �A�C�e���̊��N���X
    /// </summary>
    ItemBase();
    virtual ~ItemBase();
    /// <summary>
    /// �A�C�e���̍X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="carInfo"></param>
    virtual void Update(ItemArgumentCarInfo carInfo) = 0;
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw();
    /// <summary>
    /// �A�C�e���̌��ʔ���
    /// </summary>
    virtual void ShowEffect(ItemArgumentCarInfo carInfo);
    /// <summary>
    /// �A�C�e���̏��
    /// </summary>
    /// <returns></returns>
    ItemInfo GetItemInfo();
protected:
    //�A�C�e���̌��ʗ�
    float effecacyValue;
    //�A�C�e���̌��ʎ���
    float effecacyTime = 0;
    //�`�惂�f��
    int modelHandle;
    //�A�C�e�����g���Ă����Ԃ��ǂ���
    ItemUseSituation useSituation;
    //�A�C�e���̎�ނ�������
    Item::ItemTag itemTag;
};