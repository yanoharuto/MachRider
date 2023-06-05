#pragma once
#include <list>
class Player;
class ObjectSubject;
/// <summary>
/// �ԏ��̃}�l�[�W���[
/// </summary>
class RacerManager
{
public:
    RacerManager() {};
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
    /// <returns></returns>
    RacerManager(int cpuNum);
    //�f�X�g���N�^
    ~RacerManager();
    /// <summary>
    /// �ԏ�肽���̍X�V
    /// </summary>
    /// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
    /// <param name="circuit">����R�[�X</param>
    void RacerUpdate();
    /// <summary>
    /// �㉺�ɓ�����
    /// </summary>
    void UpDown();
    /// <summary>
    /// �`��
    /// </summary>
    /// <returns></returns>
    void Draw();
    ObjectSubject* GetPlayerSubject(int num);
private:
    Player* CreatePlayer();
    std::list<Player*> racerList;
};