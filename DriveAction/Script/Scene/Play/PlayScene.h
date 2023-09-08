#pragma once
#include "SceneBase.h"
#include <string>
#include <iostream>
#include <memory>
//�l�ɕ����ď������s��

#define PlaySceneProcess 3
class Menu;
class PostGameEndStagingProcess;
class PrePlayGameProcess;
class PlayGameProcess;
class ActorControllerManager;
class GameCamera;
class ShadowMap;
class ConflictManager;
class GameScreen;
class PlayerObserver;
class CollectItemObserver;
/// <summary>
/// �Q�[����V�ԃV�[��
/// </summary>
class PlayScene final: public SceneBase
{
public:
    /// <summary>
    /// ���j���[��ʂƃQ�[���̗���̊m�ۂƉ������[�h
    /// </summary>
    PlayScene();
    /// <summary>
    /// ���j���[�ƃQ�[���̊J��
    /// </summary>
    ~PlayScene() override;
    /// <summary>
    /// �Q�[����V��
    /// </summary>
    /// <returns></returns>
    SceneType Update() override;
    /// <summary>
    /// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
    /// </summary>
    void Draw()const override;
private:
    /// <summary>
    /// �G�t�F�N�g�̍X�V����
    /// </summary>
    void UpdateEffect();
    /// <summary>
    /// �J�E���g�_�E���I���܂ł̏���
    /// </summary>
    void UpdatePreCountdownEnd();
    /// <summary>
    /// �V��ł���Ƃ��̏���
    /// </summary>
    void UpdatePlayGame();
    /// <summary>
    /// �S�������̏���
    /// </summary>
    void UpdatePoatGameEndProcess();
    //�Q�[�����f�@�\
    Menu* menu;
    //�S�[����̏���
    PostGameEndStagingProcess* postGameEndProcess;
    //�V��ł���Ƃ��̏���
    PlayGameProcess* playGameProcess;
    //���[�X�O�̏���
    PrePlayGameProcess* gamePrevProcess;
    //�J����
    GameCamera* camera;
    //�V���h�E�}�b�v
    ShadowMap* shadowMap;
    //�Փ˔�����N���X
    ConflictManager* conflictManager;
    //�e�I�u�W�F�N�g�̊Ǘ���
    std::shared_ptr<ActorControllerManager> controllerManager;
    //�v���C���[�̏��ʒB�N���X
    std::shared_ptr<PlayerObserver> playerObserver;
    //���W�A�C�e���̊Ǘ��N���X
    std::shared_ptr<CollectItemObserver>  collectItemObserver;
    //�`��󋵂�ۑ�����
    GameScreen* screen;
    /// <summary>
    /// �v���C�V�[���̒i�K
    /// </summary>
    enum PlaySceneProgress
    {
        start,//�ŏ��̏���
        game,//�V��ł���Ƃ��̏���
        postGameEnd,//�S�[�����I��������̏���
    };
    //�����̏������s�������߂�ϐ�
    PlaySceneProgress nowProgress;
    //�e�V�[���̏����̊֐��|�C���^
    void (PlayScene::* UpdateFunc[PlaySceneProcess])();
};