#pragma once
#include <list>
class Actor;
/// <summary>
/// 1�̎�ނ�actor�̎q�N���X�𓮂������߂Ɏg��
/// </summary>
class ActorController
{
public:
    ActorController();
    ActorController(Actor* actor);
    virtual ~ActorController();
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update();
    /// <summary>
    /// �Q�[���J�n��������
    /// </summary>
    virtual void GameReserve() {};
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
};

