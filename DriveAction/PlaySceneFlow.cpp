#include "PlaySceneFlow.h"
#include "Utility.h"
#include "AssetManager.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "DamageObjectGenerator.h"
#include "PostGoalStaging.h"
#include "GamePlayUI.h"
#include "RacePrevProcess.h"
#include "RaceScreen.h"
#include "EffekseerForDXLib.h"
#include "RaceCamera.h"
#include "ChallengeFlow.h"
#include "ResultScore.h"
#include "Rule.h"
#include "StageInitializer.h"
#include "SoundPlayer.h"
#include "ShadowMap.h"
#include "UIManager.h"
#include "Menu.h"
#include "FadeInFadeOut.h"
/// <summary>
/// ゲームしているときの流れ
/// </summary>
PlaySceneFlow::PlaySceneFlow()
{
	conflictManager = new ConflictManager();
	controllerManager = new ActorControllerManager();
	StageInitializer* stageInitializer = new StageInitializer();
	modelManager = new AssetManager();
	stageInitializer->Init(controllerManager);
	playerObserver = stageInitializer->GetPlayerObserver();
	gameLimitTimer = new Timer(stageInitializer->GetGameTime());
	challenge = new ChallengeFlow(playerObserver);
	playerUI = new GamePlayUI(gameLimitTimer, challenge,playerObserver);
	camera = new RaceCamera(playerObserver);
	shadowMap = new ShadowMap(playerObserver);
	score = new ResultScore(gameLimitTimer, playerObserver);
	nowProgress = PlaySceeneProgress::start;
	postGoalStaging = nullptr;
	racePrevProccess = new RacePrevProcess();
	screen = new RaceScreen();
	
	SAFE_DELETE(stageInitializer);
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
	SAFE_DELETE(score);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(challenge);
	SAFE_DELETE(controllerManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(challenge);
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
	//メニュー画面を開いているときは暗くして一時停止
	if (Menu::IsMenuOpen())
	{
		SetDrawBright(menuBright, menuBright, menuBright);
		screen->Draw();
		SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
	}
	else
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
			SetDrawBright(menuBright, menuBright, menuBright);
			screen->Draw();
			SetDrawBright(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE);
			postGoalStaging->Draw();
			break;
		}
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
	challenge->Update(controllerManager);
	playerUI->Update(challenge);
	camera->Update();
	//シャドウマップの範囲を更新
	shadowMap->SetShadowMapErea();

	//レース終了
	if (gameLimitTimer->IsOverLimitTime() || challenge->IsEndingChallenge())
	{
		nowProgress = PlaySceeneProgress::playerGoal;		
		//ゴール後の処理をお願い
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
	if (postGoalStaging->Update(score))
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
	challenge->Update(controllerManager);
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
