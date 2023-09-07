#pragma once
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
class Actor;
class DrawModel;
/// <summary>
/// 1�̎�ނ�actor�̎q�N���X�𓮂������߂Ɏg��
/// </summary>
class ActorController abstract
{
public:
    /// <summary>
    /// ���삷��I�u�W�F�N�g�̖��O��������
    /// </summary>
    ActorController(ObjectInit::InitObjKind kind) { controllObjKind = kind; };
    /// <summary>
    /// �`����ƃI�u�W�F�N�g�̃f���[�g
    /// </summary>
    virtual ~ActorController();
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update();
    /// <summary>
    /// �Q�[���J�n��������
    /// </summary>
    virtual void PrepareGame();
    /// <summary>
    /// �`�揈��
    /// </summary>
    virtual void Draw()const;
protected:
    /// <summary>
    /// �`�����ActorList�̉��
    /// </summary>
    void DeleteActorListAndDrawModel();
    //���̃��X�g����
    std::list<Actor*> actorList;
    //�`��S��
    DrawModel* drawModel = nullptr;
    //���삷��I�u�W�F�N�g�̎��
    ObjectInit::InitObjKind controllObjKind;
};