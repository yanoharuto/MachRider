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
/// カメラや当たり判定やゲームオブジェクトなどを確保
/// </summary>
GameManager::GameManager()
{
	//衝突判定管理
	conflictManager = new ConflictManager();
	//様々なオブジェクトの更新などをする
	controllerManager = new ActorControllerManager();
	//ステージごとの配置などを行う
	controllerManager->AddActorController(new StageObjectController());
	//プレイヤーの情報を更新するオブザーバー
	PlayerCarController* playerP = new PlayerCarController();
	controllerManager->AddActorController(std::move(playerP));
	//収集アイテムコントローラーを追加
	controllerManager->AddActorController(new CollectController());
	//カメラ
	camera = new GameCamera(playerP->CreatePlayerObserver());
	//影
	shadowMap = new ShadowMap(playerP->CreatePlayerObserver());
	//描画するたび保存出来るクラス
	screen = new GameScreen();
	//カメラの処理
	camera->Update();
	playerObserver = playerP->CreatePlayerObserver();
}
/// <summary>
/// 各クラスを開放
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
/// 各クラスの更新
/// </summary>
void GameManager::Update()
{
	controllerManager->Update();
	conflictManager->Update();
	camera->Update();
	shadowMap->SetShadowMapErea();
}
/// <summary>
/// ゲーム始める前の更新
/// </summary>
void GameManager::PrepareGame()
{
	controllerManager->PrepareGame();
	camera->Update();
	shadowMap->SetShadowMapErea();
}
/// <summary>
/// 描画画面を保存
/// </summary>
void GameManager::SaveDrawScreen()
{
	screen->ScreenUpdate();
}
/// <summary>
/// 各オブジェクトの描画と影を描画
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
/// プレイヤーの情報通達クラスを渡す
/// </summary>
/// <returns>プレイヤーの情報通達クラス</returns>
std::weak_ptr<PlayerObserver> GameManager::GetPlayerObserver()
{
	return playerObserver;
}
