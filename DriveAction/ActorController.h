#pragma once
#include <list>
#include <vector>
#include "EditObjectData.h"
#include "InitObjKind.h"
class Actor;
class ModelViewer;
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
    virtual ~ActorController();
    /// <summary>
    /// ���X�g�ɒǉ�
    /// </summary>
    /// <param name="editData"></param>
    virtual void AddObject(std::vector<EditArrangementData> editData) {};
    /// <summary>
    /// ���삵�Ă���I�u�W�F�N�g�̎��
    /// </summary>
    /// <returns></returns>
    virtual ObjectInit::InitObjKind GetControllObjKind() { return controllObjKind; };
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update();
    /// <summary>
    /// �Q�[���J�n��������
    /// </summary>
    virtual void GameReserve();
    /// <summary>
    /// �`�揈��
    /// </summary>
    virtual void Draw()const;
    /// <summary>
    /// �������I���Ă���false
    /// </summary>
    /// <returns></returns>
    virtual bool IsAlive()const;
protected:
    //���̃��X�g����
    std::list<Actor*> actorList;
    //�`��S��
    ModelViewer* viewer = nullptr;
    //���삷��I�u�W�F�N�g�̎��
    ObjectInit::InitObjKind controllObjKind;
};