#pragma once
#include <list>
class ActorController;
class DamageObjectGenerator;
class EnemyGenerator;
/// <summary>
/// actor�̓����𐧌䂵�Ă��镨��S�����˂ē�����
/// </summary>
class ActorControllerManager final
{
public:
    ActorControllerManager();
    ~ActorControllerManager();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Q�[���J�n�O�X�V
    /// </summary>
    void GameReserve();
    /// <summary>
    /// �e�A�N�^�[�̕`��
    /// </summary>
    void Draw()const;
    /// <summary>
    /// actor�Ǘ��N���X��ǉ�
    /// </summary>
    /// <param name="actorController"></param>
    void AddActorController(ActorController* actorController);
private:
    /// <summary>
    ///�@�G��������
    /// </summary>
    void GenerateEnemyProcess();
    //���W�A�C�e���̐�
    int collectNum = 0;
    //actor�Ǘ��N���X�̃��X�g
    static std::list<ActorController*> actorControllerList;
    //�G�����˂��Ă����肵���A�C�e�����쐬
    DamageObjectGenerator* damageObjGenerator;
    //���W�A�C�e������������Ƒ�����G���쐬����
    EnemyGenerator* enemyGenerator;
};

