#include "PlaySceneFlow.h"
#include "Utility.h"
#include "AssetManager.h"
#include "CoinManager.h"
#include "ConflictManager.h"
#include "DamageObjectGenerator.h"
#include "FlyShipManager.h"
#include "FiringItemManager.h"
#include "PostGoalStaging.h"
#include "PlayerRelatedUI.h"
#include "RacePrevProcess.h"
#include "RaceScreen.h"
#include "EffekseerForDXLib.h"
#include "RaceCamera.h"
#include "RacerManager.h"
#include "ResultScore.h"
#include "Rule.h"
#include "StageManager.h"
#include "SoundPlayer.h"
#include "ShadowMap.h"
#include "UIManager.h"
#include "Menu.h"
/// <summary>
/// ゲームしているときの流れ
/// </summary>
PlaySceneFlow::PlaySceneFlow()
{

	conflictManager = new ConflictManager();
	racerManager = new RacerManager(1);
	stageManager = new StageManager();
	camera = new RaceCamera(racerManager);
	nowProgress = PlaySceeneProgress::start;
	gameLimitTimer = new Timer(MAX_GAME_TIME);
	postGoalStaging = nullptr;
	score = nullptr;
	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	coinManager = new CoinManager();
	flyShipManager = new FlyShipManager(racerManager); 
	shadowMap = new ShadowMap(racerManager);
	stageManager = new StageManager();
	racePrevProccess = new RacePrevProcess();
	screen = new RaceScreen();
	playerUI = new PlayerRelatedUI(gameLimitTimer,coinManager->GetCoinFirstNum(),racerManager);
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
	SAFE_DELETE(racerManager)
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playerUI);
	SAFE_DELETE(score);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(flyShipManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(racePrevProccess);
	SAFE_DELETE(coinManager);
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
void PlaySceneFlow::Draw()
{	
	if (Menu::IsMenuOpen())
	{
		SetDrawBright(60, 60, 60);
		screen->Draw();
		SetDrawBright(255, 255, 255);
	}
	else
	{
		UseShadowMap();
		switch (nowProgress)
		{
		case PlaySceeneProgress::start:
			screen->ScreenUpdate();
			racePrevProccess->Draw();
			DrawEffekseer3D();
			DrawEffekseer2D();
			break;
		case PlaySceeneProgress::game:
			screen->ScreenUpdate();
			DrawEffekseer3D();
			DrawEffekseer2D();
			playerUI->Draw();
			conflictManager->DrawCollisionSphere();
			break;
		case PlaySceeneProgress::playerGoal:
			SetDrawBright(60, 60, 60);
			screen->Draw();
			SetDrawBright(255, 255, 255);
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
void PlaySceneFlow::DrawManagers()
{
	if (nowProgress != PlaySceeneProgress::playerGoal)
	{
		firingManager->Draw();
		racerManager->Draw();
		flyShipManager->Draw();
		stageManager->Draw();
		coinManager->Draw();
	}
}
/// <summary>
/// シャドウマップを使う
/// </summary>
void PlaySceneFlow::UseShadowMap()
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
	coinManager->Update();
	racerManager->RacerUpdate();
	flyShipManager->Update();

	//飛び道具の更新
	firingManager->Update();
	
	conflictManager->Update();
	
	playerUI->Update(coinManager);
	
	camera->Update();
	//シャドウマップの範囲を更新
	shadowMap->SetShadowMapErea();

	//レース終了
	if (gameLimitTimer->IsOverLimitTime() || coinManager->GetRemainingCoin() == 0)
	{
		nowProgress = PlaySceeneProgress::playerGoal;
		score = new ResultScore(gameLimitTimer, racerManager);
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
	if (postGoalStaging->Update())
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
	racerManager->UpDown();
	//コインの更新
	coinManager->Update();
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
