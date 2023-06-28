#include "PlaySceneFlow.h"
#include "Utility.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "DamageObjectGenerator.h"
#include "PostGoalStaging.h"
#include "GamePlayUI.h"
#include "RacePrevProcess.h"
#include "RaceScreen.h"
#include "EffekseerForDXLib.h"
#include "RaceCamera.h"
#include "CollectController.h"
#include "ResultScore.h"
#include "Rule.h"
#include "StageInitializer.h"
#include "SoundPlayer.h"
#include "ShadowMap.h"
#include "UIManager.h"
#include "Menu.h"
#include "FadeInFadeOut.h"
#include "CollectController.h"
/// <summary>
/// ゲームしているときの流れ
/// </summary>
PlaySceneFlow::PlaySceneFlow()
{
	//衝突判定管理
	conflictManager = new ConflictManager();
	//様々なオブジェクトの更新などをする
	controllerManager = new ActorControllerManager();
	//ステージごとの配置などを行う
	StageInitializer* stageInitializer = new StageInitializer();
	stageInitializer->Init(controllerManager);
	player = stageInitializer->GetPlayerObserver();
	
	//収集アイテムコントローラーを追加
	controllerManager->AddActorController(new CollectController());
	//ゲーム終了タイマー
	gameLimitTimer = new Timer(stageInitializer->GetGameTime());
	//UIを追加
	playerUI = new GamePlayUI(gameLimitTimer, player);
	//カメラ
	camera = new RaceCamera(player);
	//影
	shadowMap = new ShadowMap(player);
	//現在の処理
	nowProgress = PlaySceeneProgress::start;
	//ゴール後の処理はまだ呼ばない
	postGoalStaging = nullptr;
	//ゴール前処理
	racePrevProccess = new RacePrevProcess();
	//描画するたび保存
	screen = new RaceScreen();
	
	SAFE_DELETE(stageInitializer);
	//書く処理を分ける
	UpdateFunc[PlaySceneFlow::start] = &PlaySceneFlow::StartUpdate;
	UpdateFunc[PlaySceneFlow::game] = &PlaySceneFlow::GameUpdate;
	UpdateFunc[PlaySceneFlow::playerGoal] = &PlaySceneFlow::PlayerGoalUpdate;
	UpdateFunc[PlaySceneFlow::end] = &PlaySceneFlow::EndUpdate;
	//カメラの処理
	camera->Update();
#ifdef _DEBUG
#endif
}

PlaySceneFlow::~PlaySceneFlow()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playerUI);
	SAFE_DELETE(controllerManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(racePrevProccess);
	SAFE_DELETE(gameLimitTimer);
	SAFE_DELETE(screen);
	

#ifdef _DEBUG
#endif

}
/// <summary>
/// 更新
/// </summary>
void PlaySceneFlow::Update()
{
	if (!Menu::IsMenuOpen())
	{
		//各流れの処理
		(this->*UpdateFunc[nowProgress])();

		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();
		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer3D();
		UpdateEffekseer2D();
	}
#ifdef _DEBUG
#endif
}
/// <summary>
/// 描画
/// </summary>
void PlaySceneFlow::Draw()const
{
	//描画処理
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		UseShadowMapDraw();
		DrawEffekseer3D();
		DrawEffekseer2D();
		racePrevProccess->Draw();
		screen->ScreenUpdate();
		break;
	case PlaySceeneProgress::game:
		UseShadowMapDraw();
		DrawEffekseer3D();
		DrawEffekseer2D();
		playerUI->Draw();
		screen->ScreenUpdate();
		break;
	case PlaySceeneProgress::playerGoal:
		postGoalStaging->Draw();
		break;
	}

#ifdef DEBUG

#endif // DEBUG

}
/// <summary>
/// マネージャーの描画関数を呼び出す
/// </summary>
void PlaySceneFlow::DrawManagers()const
{
	if (nowProgress != PlaySceeneProgress::playerGoal)
	{
		controllerManager->Draw();
	}
}
/// <summary>
/// シャドウマップを使った描画
/// </summary>
void PlaySceneFlow::UseShadowMapDraw()const
{
	shadowMap->SetUP();
	DrawManagers();
	shadowMap->DrawEnd();
	DrawManagers();
	shadowMap->Use();

}
/// <summary>
/// 遊んでいるときの処理
/// </summary>
void PlaySceneFlow::GameUpdate()
{
	controllerManager->Update();
	conflictManager->Update();
	playerUI->Update();
	camera->Update();
	//シャドウマップの範囲を更新
	shadowMap->SetShadowMapErea();

	//ゲーム終了
	if (gameLimitTimer->IsOverLimitTime() || CollectController::IsEndingChallenge())
	{
		ResultScore::FixScore(gameLimitTimer, player);
		nowProgress = PlaySceeneProgress::playerGoal;		
		postGoalStaging = new PostGoalStaging();
	}
}
/// <summary>
/// 最後の処理
/// </summary>
void PlaySceneFlow::EndUpdate()
{
	nextSceneType = SceneType::TITLE;
	isEndProccess = true;
}
/// <summary>
/// ゴール後の処理
/// </summary>
void PlaySceneFlow::PlayerGoalUpdate()
{
	postGoalStaging->Update();
	if (postGoalStaging->IsEndProcess())
	{
		nowProgress = PlaySceeneProgress::end;
	}
}
/// <summary>
/// 初めにする処理
/// </summary>
void PlaySceneFlow::StartUpdate()
{
	racePrevProccess->Update();
	controllerManager->GameReserve();
	//カメラの処理
	camera->Update();
	//シャドウマップの更新
	shadowMap->SetShadowMapErea();
	//処理が終わったら
	if (racePrevProccess->IsProccesEnd())
	{
		nowProgress = PlaySceeneProgress::game;
		SoundPlayer::Play2DSE(playBGM);
		gameLimitTimer->Init();
	}
}
