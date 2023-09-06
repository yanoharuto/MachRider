#include "GameManager.h"
#include "GameCamera.h"
#include "ShadowMap.h"
#include "UIManager.h"
#include "CollectController.h"
#include "PlayeCarController.h"
#include "StageObjectController.h"
#include "PlayerObserver.h"
#include "ConflictManager.h"
#include "ActorControllerManager.h"
#include "Timer.h"
#include "ReusableTimer.h"
#include "GameScreen.h"
#include "Utility.h"
/// <summary>
/// �J�����ⓖ���蔻���Q�[���I�u�W�F�N�g�Ȃǂ��m��
/// </summary>
GameManager::GameManager()
{
	//�Փ˔���Ǘ�
	conflictManager = new ConflictManager();
	//�l�X�ȃI�u�W�F�N�g�̍X�V�Ȃǂ�����
	controllerManager = new ActorControllerManager();
	//�X�e�[�W���Ƃ̔z�u�Ȃǂ��s��
	controllerManager->AddActorController(new StageObjectController());
	//�v���C���[�̏����X�V����I�u�U�[�o�[
	PlayerCarController* playerP = new PlayerCarController();
	controllerManager->AddActorController(std::move(playerP));
	//���W�A�C�e���R���g���[���[��ǉ�
	controllerManager->AddActorController(new CollectController());
	//�J����
	camera = new GameCamera(playerP->CreatePlayerObserver());
	//�e
	shadowMap = new ShadowMap(playerP->CreatePlayerObserver());
	//�`�悷�邽�ѕۑ��o����N���X
	screen = new GameScreen();
	//�J�����̏���
	camera->Update();
	playerObserver = playerP->CreatePlayerObserver();
}
/// <summary>
/// �e�N���X���J��
/// </summary>
GameManager::~GameManager()
{
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(controllerManager);
	SAFE_DELETE(screen);
	SAFE_DELETE(camera);
	playerObserver.reset();
}
/// <summary>
/// �e�N���X�̍X�V
/// </summary>
void GameManager::Update()
{
	controllerManager->Update();
	conflictManager->Update();
	camera->Update();
	shadowMap->SetShadowMapErea();
}
/// <summary>
/// �Q�[���n�߂�O�̍X�V
/// </summary>
void GameManager::PrepareGame()
{
	controllerManager->PrepareGame();
	camera->Update();
	shadowMap->SetShadowMapErea();
}
/// <summary>
/// �`���ʂ�ۑ�
/// </summary>
void GameManager::SaveDrawScreen()
{
	screen->ScreenUpdate();
}
/// <summary>
/// �e�I�u�W�F�N�g�̕`��Ɖe��`��
/// </summary>
void GameManager::DrawActor() const
{
	shadowMap->SetUP();
	controllerManager->Draw();
	shadowMap->DrawEnd();
	controllerManager->Draw();
	shadowMap->Use();
}
/// <summary>
/// �v���C���[�̏��ʒB�N���X��n��
/// </summary>
/// <returns>�v���C���[�̏��ʒB�N���X</returns>
std::weak_ptr<PlayerObserver> GameManager::GetPlayerObserver()
{
	return playerObserver;
}
