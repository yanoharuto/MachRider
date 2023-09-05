#pragma once
#include <iostream>
#include <memory>
class GameCamera;
class ShadowMap;
class ConflictManager;
class ActorControllerManager;
class PlayerObserver;
class GameScreen;
class ReusableTimer;
class Timer;
/// <summary>
/// �Q�[���œ��������߂ɕK�v�ȕ����܂Ƃ߂�����
/// </summary>
class GameManager final
{
public:
    /// <summary>
    /// �J�����ⓖ���蔻���Q�[���I�u�W�F�N�g�Ȃǂ��m��
    /// </summary>
    GameManager();
    /// <summary>
    /// �e�N���X���J��
    /// </summary>
    ~GameManager();
    /// <summary>
    /// �e�N���X�̍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// �Q�[���n�߂�O�̍X�V
    /// </summary>
    void PrepareGame();
    /// <summary>
    /// �`���ʂ�ۑ�
    /// </summary>
    void SaveDrawScreen();
    /// <summary>
    /// �e�I�u�W�F�N�g�̕`��Ɖe��`��
    /// </summary>
    void DrawActor()const;
    /// <summary>
    /// �v���C���[�̏��ʒB�N���X��n��
    /// </summary>
    /// <returns>�v���C���[�̏��ʒB�N���X</returns>
    std::weak_ptr<PlayerObserver> GetPlayerObserver();
private:
    //�v���C���[�̏��ʒB�N���X
    std::weak_ptr<PlayerObserver> playerObserver;
    //�J����
    GameCamera* camera;
    //�V���h�E�}�b�v
    ShadowMap* shadowMap;
    //�Փ˔�����N���X
    ConflictManager* conflictManager;
    //�e�I�u�W�F�N�g�̊Ǘ���
    ActorControllerManager* controllerManager;
    //�`��󋵂�ۑ�����
    GameScreen* screen;
};