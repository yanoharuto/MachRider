#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include <iostream>
class ObjectObserver;
class DamageObjectController;
class ActorControllerManager;
/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
class DamageObjectGenerator final
{
public:
    /// <summary>
    /// �_���[�W����̂��镨�̎��
    /// </summary>
    enum DamageObjectKind
    {
        bomber,
        littleRadLaser,
        bigRadLaser
    };
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    DamageObjectGenerator(ActorControllerManager* const controllerManager);
    ~DamageObjectGenerator();
    /// <summary>
    /// �_���[�W��^����I�u�W�F�N�g�𐶐�
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">���˂����l�̏���n��</param>
    /// <returns></returns>
    static void GenerateDamageObject(DamageObjectKind itemTag, std::unique_ptr<ObjectObserver> sub);
private:
    //�쐬�����R���g���[���[�N���X�BGetControllerList���Ă΂��Ə����������
    static std::unordered_map<DamageObjectKind, DamageObjectController*> controllerVec;
    
};