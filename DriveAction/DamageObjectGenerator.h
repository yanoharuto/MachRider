#pragma once
#include <list>

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
    DamageObjectGenerator();
    ~DamageObjectGenerator();
    /// <summary>
    /// �_���[�W��^����I�u�W�F�N�g�𐶐�
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="sub">���˂����l�̏���n��</param>
    /// <returns></returns>
    static void GenerateDamageObject(DamageObjectKind itemTag,ObjectSubject* sub);
    /// <summary>
    /// �������ꂽ�I�u�W�F�N�g��controllerManager�ɒǉ�
    /// </summary>
    /// <param name="controllerManager"></param>
    void MoveControllerList(ActorControllerManager* controllerManager);
private:
    //�쐬�����R���g���[���[�N���X�BGetControllerList���Ă΂��Ə����������
    static std::list<ActorController*> createDamageObject;
};