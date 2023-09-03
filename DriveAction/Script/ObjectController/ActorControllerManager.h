#pragma once
#include <list>
class AddableObjectController;
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
/// <summary>
/// actor�̓����𐧌䂵�Ă��镨��S�����˂ē�����
/// </summary>
class ActorControllerManager final
{
public:
    /// <summary>
    /// �G�Ȃǂ�New���Ĕz�u����
    /// </summary>
    ActorControllerManager();
    /// <summary>
    /// �G�̊Ǘ��N���X��X�e�[�W�̃I�u�W�F�N�g�Ȃǂ����ׂĉ��
    /// </summary>
    ~ActorControllerManager();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Q�[���J�n�O�X�V
    /// </summary>
    void PrepareGame();
    /// <summary>
    /// �e�A�N�^�[�̕`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// actor�Ǘ��N���X��ǉ�
    /// </summary>
    /// <param name="actorController">actor�Ǘ��N���X</param>
    void AddActorController(ActorController* actorController);
private:
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����Q�[���J�n�O�X�V
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void PrepareGame(std::list<controllerClass*> controllerList);
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����X�V
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void Update(std::list<controllerClass*> controllerList);
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����`��
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void Draw(std::list<controllerClass*> controllerList)const;
    /// <summary>
    ///�@�G��������
    /// </summary>
    void GenerateEnemyProcess();
    //���W�A�C�e���̐�
    int collectNum = 0;
    //actor�Ǘ��N���X�̃��X�g
    std::list<ActorController*> actorControllerList;
    //�ǉ��\�N���XActor�Ǘ��N���X�̃��X�g
    std::list<AddableObjectController*> addableActorControllerList;
    //�G�����˂��Ă����肵���A�C�e�����쐬
    DamageObjectGenerator* damageObjGenerator;
    //���W�A�C�e������������Ƒ�����G���쐬����
    EnemyGenerator* enemyGenerator;
};