#pragma once
#include <list>
#include <memory>
#include <iostream>
class AddableObjectController;
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
class BomberController;
class RotatingLaserController;
class CollectItemObserver;
class CameraObserver;
/// <summary>
/// actor�̓����𐧌䂵�Ă��镨��S�����˂ē�����
/// </summary>
class ActorControllerManager final
{
public:
    /// <summary>
    /// �Q�[�����Ɏg���I�u�W�F�N�g�̊Ǘ��N���X�̊m��
    /// </summary>
    /// <param name="collectItemObserver">���W�A�C�e�������ꂽ�肵���狳���Ă��炤</param>
    ActorControllerManager(std::shared_ptr<CollectItemObserver> collectItemObserver);
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
    void Draw(std::weak_ptr<CameraObserver> cameraObserever)const;
    /// <summary>
    /// actor�Ǘ��N���X��ǉ�
    /// </summary>
    /// <param name="actorController">actor�Ǘ��N���X</param>
    void AddActorController(std::shared_ptr<ActorController> actorController);
private:
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����Q�[���J�n�O�X�V
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void PrepareGame(std::list<std::shared_ptr<controllerClass>> controllerList);
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����X�V
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void Update(std::list<std::shared_ptr<controllerClass>> controllerList);
    /// <summary>
    /// 2��Actor�Ǘ��N���X�ǂ���ł��g����`��
    /// </summary>
    /// <typeparam name="controllerClass">Actor�Ǘ��N���X</typeparam>
    /// <param name="controllerList">controllerClass��Z�߂����X�g</param>
    template<typename controllerClass>
    void Draw(std::list<std::shared_ptr<controllerClass>> controllerList, std::weak_ptr<CameraObserver> cameraObserever)const;
    /// <summary>
    ///�@�G��������
    /// </summary>
    void GenerateEnemyProcess();
    //���W�A�C�e���̐�
    int collectNum = 0;
    //�F��ȃI�u�W�F�N�g�̊Ǘ��N���X
    std::list<std::shared_ptr<ActorController>> actorControllerList;
    //�ǉ��\�N���XActor�Ǘ��N���X�̃��X�g
    std::list<std::shared_ptr<AddableObjectController>> addableActorControllerList;
    //�G�����˂��Ă����肵���A�C�e�����쐬
    std::shared_ptr<DamageObjectGenerator> damageObjGenerator;
    //���W�A�C�e����������ꂽ���ǂ����������Ă��炤
    std::shared_ptr<CollectItemObserver> collectObserver;
    //���W�A�C�e������������Ƒ�����G���쐬����
    EnemyGenerator* enemyGenerator;
};