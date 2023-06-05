#pragma once
#include <string>
#include "ItemTag.h"
class ObjectSubject;
class DamageObject;
class ObjectObserver;
/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
class DamageObjectGenerator
{
public:
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    DamageObjectGenerator();
    ~DamageObjectGenerator();
    /// <summary>
    /// �A�C�e���̎�ނɂ���Đ�������A�C�e����ύX����
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static DamageObject* GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub);
};