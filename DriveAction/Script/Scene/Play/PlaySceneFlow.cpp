#include "PlaySceneFlow.h"
#include "Utility.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "PlayGameProcess.h"
#include "PostGameEndStagingProcess.h"
#include "GamePrevProcess.h"
#include "EffekseerForDXLib.h"
#include "GameCamera.h"
#include "GameScreen.h"
#include "ShadowMap.h"
#include "PlayerObserver.h"
#include "PlayerCarController.h"
#include "CollectController.h"
#include "CollectItemObserver.h"

/// <summary>
/// ゲームしているときの流れ
/// </summary>
PlaySceneFlow::PlaySceneFlow()
{
	//現在の処理
	nowProgress = PlaySceneProgress::start;
	//ゴール後の処理とプレイヤーが操作する処理はまだ呼ばない
	postGoalStaging = nullptr;
	playGameProcess = nullptr;
	//衝突判定管理
	conflictManager = new ConflictManager();
	//収集アイテム
	std::shared_ptr<CollectItemController> collectController = std::make_shared<CollectItemController>();
	collectItemObserver = std::make_shared<CollectItemObserver>(collectController);
	//様々なオブジェクトの更新などをする
	controllerManager = std::make_shared<ActorControllerManager>(collectItemObserver);
	//収集アイテムを共有
	controllerManager->AddActorController(collectController);
	//共有し終わったので開放
	collectController.reset();
	//プレイヤー
	std::shared_ptr<PlayerCarController> playerController = std::make_shared<PlayerCarController>();
	//プレイヤーの情報を更新するオブザーバー
	playerObserver = playerController->CreatePlayerObserver();
	//プレイヤーを共有
	controllerManager->AddActorController(playerController);
	//解放
	playerController.reset();
	//ゴール前処理
	gamePrevProcess = new GamePrevProcess(collectItemObserver);
	//カメラ
	camera = new GameCamera(playerObserver);
	//影
	shadowMap = new ShadowMap(playerObserver);
	//描画するたび保存出来るクラス
	screen = new GameScreen();
	//カメラの処理
	camera->Update();
	//書く処理を分ける
	UpdateFunc[PlaySceneFlow::start] = &PlaySceneFlow::StartUpdate;
	UpdateFunc[PlaySceneFlow::game] = &PlaySceneFlow::GameUpdate;
	UpdateFunc[PlaySceneFlow::playerGoal] = &PlaySceneFlow::PlayerGoalUpdate;
	UpdateFunc[PlaySceneFlow::end] = &PlaySceneFlow::EndUpdate;
}
/// <summary>
/// オブジェクトやカメラ、UIタイマーなどを削除
/// </summary>
PlaySceneFlow::~PlaySceneFlow()
{
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(screen);
	SAFE_DELETE(camera);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playGameProcess);
	SAFE_DELETE(gamePrevProcess);
	controllerManager.reset();
}
/// <summary>
/// 更新
/// </summary>
void PlaySceneFlow::Update()
{
	//各流れの処理
	(this->*UpdateFunc[nowProgress])();
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	UpdateEffekseer2D();
}
/// <summary>
/// 描画
/// </summary>
void PlaySceneFlow::Draw()const
{
	//描画処理
	switch (nowProgress)
	{
		//スタート前のカウントダウン
	case PlaySceneProgress::start:
		controllerManager->Draw();
		//エフェクト
		DrawEffekseer3D();
		DrawEffekseer2D();
		gamePrevProcess->Draw();
		//描画を保存
		screen->ScreenUpdate();
		break;
		//遊んでいるとき
	case PlaySceneProgress::game:
		controllerManager->Draw();
		//エフェクト
		DrawEffekseer3D();
		DrawEffekseer2D();
		playGameProcess->Draw();
		//描画を保存
		screen->ScreenUpdate();
		break;
		//スコアの描画
	case PlaySceneProgress::playerGoal:
		postGoalStaging->Draw();
		break;
	}
}
/// <summary>
/// 遊んでいるときの処理
/// </summary>
void PlaySceneFlow::GameUpdate()
{
	//ゲームを遊んでいるときの処理
	playGameProcess->Update(collectItemObserver);
	controllerManager->Update();
	conflictManager->Update();
	camera->Update();
	shadowMap->SetShadowMapErea();
	//遊んでいるときの処理が終了したら
	if(playGameProcess->IsEndProcess())
	{
		postGoalStaging = new PostGameEndStagingProcess(playerObserver, playGameProcess->GetGameTimer());
		SAFE_DELETE(playGameProcess);
		nowProgress = PlaySceneProgress::playerGoal;
	}
}
/// <summary>
/// 最後の処理
/// </summary>
void PlaySceneFlow::EndUpdate()
{
	nextSceneType = SceneType::TITLE;
	isEndProcesss = true;
}
/// <summary>
/// ゴール後の処理
/// </summary>
void PlaySceneFlow::PlayerGoalUpdate()
{
	postGoalStaging->Update();
	if (postGoalStaging->IsEndProcess())
	{
		nowProgress = PlaySceneProgress::end;
	}
}
/// <summary>
/// 初めにする処理
/// </summary>
void PlaySceneFlow::StartUpdate()
{
	gamePrevProcess->Update();
	controllerManager->PrepareGame();
	camera->Update();
	shadowMap->SetShadowMapErea();
	//処理が終わったら
	if (gamePrevProcess->IsEndProcess())
	{
		nowProgress = PlaySceneProgress::game;
		SAFE_DELETE(gamePrevProcess);
		playGameProcess = new PlayGameProcess(playerObserver,collectItemObserver);
	}
}