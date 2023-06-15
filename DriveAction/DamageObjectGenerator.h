#pragma once
#include <list>
#include "ItemTag.h"
class ObjectSubject;
class DamageObject;
class ActorController;
class ActorControllerManager;
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
    /// 
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">���˂����l�̏���n��</param>
    /// <returns></returns>
    static void GenerateDamageObject(Item::ItemTag itemTag,ObjectSubject* sub);

    void GetObjectList(ActorControllerManager* controllerManager);
private:
    static std::list<ActorController*> createDamageObject;
};