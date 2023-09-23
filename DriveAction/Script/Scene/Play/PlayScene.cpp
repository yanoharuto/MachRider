#include "PlayScene.h"
#include "Utility.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "PlayGameProcess.h"
#include "PostGameEndStagingProcess.h"
#include "PrePlayGameProcess.h"
#include "EffekseerForDXLib.h"
#include "GameCamera.h"
#include "GameScreen.h"
#include "ShadowMap.h"
#include "PlayerObserver.h"
#include "PlayerCarController.h"
#include "CollectController.h"
#include "CollectItemObserver.h"
#include "CameraObserver.h"
/// <summary>
/// ���j���[��ʂƃQ�[���̗���̊m�ۂƉ������[�h
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::play)
{
    
    //���݂̏���
    nowProgress = PlaySceneProgress::start;
    //�S�[����̏����ƃv���C���[�����삷�鏈���͂܂��Ă΂Ȃ�
    postGameEndProcess = nullptr;
    playGameProcess = nullptr;
    //�Փ˔���Ǘ�
    conflictManager = new ConflictManager();
    //���W�A�C�e��
    std::shared_ptr<CollectItemController> collectController = std::make_shared<CollectItemController>();
    collectItemObserver = std::make_shared<CollectItemObserver>(collectController);
    //�l�X�ȃI�u�W�F�N�g�̍X�V�Ȃǂ�����
    controllerManager = std::make_shared<ActorControllerManager>(collectItemObserver);
    //���W�A�C�e�������L
    controllerManager->AddActorController(collectController);
    //���L���I������̂ŊJ��
    collectController.reset();
    //�v���C���[
    std::shared_ptr<PlayerCarController> playerController = std::make_shared<PlayerCarController>();
    //�v���C���[�̏����X�V����I�u�U�[�o�[
    playerObserver = playerController->CreatePlayerObserver();
    //�v���C���[�����L
    controllerManager->AddActorController(playerController);
    //���
    playerController.reset();
    //�S�[���O����
    gamePrevProcess = new PrePlayGameProcess(collectItemObserver);
    //�J����
    camera = std::make_shared<GameCamera>(playerObserver);
    cameraObserver = std::make_shared<CameraObserver>(camera);
    //�e
    shadowMap = new ShadowMap(playerObserver);
    //�`�悷�邽�ѕۑ��o����N���X
    screen = new GameScreen();
    //�J�����̏���
    camera->Update();
    //���j���[��ʂ̊J��
    menu = new Menu();
}
/// <summary>
/// ���j���[�ƃQ�[���̊J��
/// </summary>
PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(conflictManager);
    SAFE_DELETE(shadowMap);
    SAFE_DELETE(screen);
    SAFE_DELETE(postGameEndProcess);
    SAFE_DELETE(playGameProcess);
    SAFE_DELETE(gamePrevProcess);
    controllerManager.reset();
    camera.reset();
}
/// <summary>
/// �Q�[����V��
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //���j���[�Ńv���C���[������I�񂾂�
    menu->Update();
    using enum Menu::MenuOptions;
    //���j���[�̏�Ԃɂ���Ď��̃V�[����ύX    
    switch (menu->GetMenuState())
    {
        //�Q�[������蒼��
    case retry:
        nowSceneType = SceneType::reload;
        break;
        //�^�C�g���ɖ߂�
    case returnTitle:
        nowSceneType = SceneType::title;
        break;
        //�Q�[���I��
    case exitGame:
        nowSceneType = SceneType::escape;
        break;
    }

    //menu��ʂ��J���ĂȂ��Ȃ畁�ʂ̏���
    if (!menu->IsMenuOpen())
    {
        (this->*UpdateFunc[CAST_I(nowProgress)])();
    }
   
    return nowSceneType;
}
/// <summary>
/// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
/// </summary>
void PlayScene::Draw()const
{
   (this->*DrawFunc[CAST_I(nowProgress)])();
}

/// <summary>
/// �G�t�F�N�g�̍X�V����
/// </summary>
void PlayScene::UpdateEffect()
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();
    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();
    UpdateEffekseer2D();
}
/// <summary>
/// �J�E���g�_�E���I���܂ł̏���
/// </summary>
void PlayScene::UpdatePreStartCountdownEnd()
{
    gamePrevProcess->Update();
    controllerManager->PrepareGame();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    //�������I�������
    if (gamePrevProcess->IsEndProcess())
    {
        nowProgress = PlaySceneProgress::game;
        SAFE_DELETE(gamePrevProcess);
        playGameProcess = new PlayGameProcess(playerObserver, collectItemObserver);
    }
}
/// <summary>
/// �V��ł���Ƃ��̏���
/// </summary>
void PlayScene::UpdatePlayGame()
{
    //�Q�[����V��ł���Ƃ��̏���
    playGameProcess->Update(collectItemObserver);
    controllerManager->Update();
    conflictManager->Update();
    camera->Update();
    shadowMap->SetShadowMapArea();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    //�V��ł���Ƃ��̏������I��������
    if (playGameProcess->IsEndProcess())
    {
        postGameEndProcess = new PostGameEndStagingProcess(playerObserver, playGameProcess->GetGameTimer());
        SAFE_DELETE(playGameProcess);
        controllerManager.reset();
        nowProgress = PlaySceneProgress::postGameEnd;
    }
}
/// <summary>
/// �S�������̏���
/// </summary>
void PlayScene::UpdatePostGameEndProcess()
{
    postGameEndProcess->Update();
    //�G�t�F�N�g�̍X�V
    UpdateEffect();
    if (postGameEndProcess->IsEndProcess())
    {
        nowSceneType = SceneType::title;
    }
}
/// <summary>
/// �J�E���g�_�E���I���܂ł̕`��
/// </summary>
void PlayScene::DrawPreStartCountdownEnd()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else//�V��ł���Ƃ��̏�Ԃ�`��
    {
        controllerManager->Draw(cameraObserver);
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        gamePrevProcess->Draw();
        //�`���ۑ�
        screen->ScreenUpdate();
    }
}
/// <summary>
/// �V��ł���Ƃ��̕`��
/// </summary>
void PlayScene::DrawPlayGame()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else//�V��ł���Ƃ��̏�Ԃ�`��
    {
        controllerManager->Draw(cameraObserver);
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        playGameProcess->Draw();
        //�`���ۑ�
        screen->ScreenUpdate();
    }
}
/// <summary>
/// �S���A�C�e�������������̏���
/// </summary>
void PlayScene::DrawPostGameEndProcess()const
{
    if (menu->IsMenuOpen())//���j���[���J���Ă����烁�j���[��ʂ�`��
    {
        menu->Draw();
    }
    else
    {
        //�G�t�F�N�g
        DrawEffekseer3D();
        DrawEffekseer2D();
        postGameEndProcess->Draw();
    }
}