#include "PlaySceneFlow.h"
#include "Utility.h"
#include "ActorControllerManager.h"
#include "ConflictManager.h"
#include "PlayGameProcess.h"
#include "PostGameEndStagingProcess.h"
#include "GamePrevProcess.h"
#include "EffekseerForDXLib.h"
#include "GameManager.h"
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
	//ゴール前処理
	gamePrevProcess = new GamePrevProcess();
	gameManager = std::make_shared<GameManager>();
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
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playGameProcess);
	SAFE_DELETE(gamePrevProcess);
	gameManager.reset();
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
		gameManager->DrawActor();
		//エフェクト
		DrawEffekseer3D();
		DrawEffekseer2D();
		gamePrevProcess->Draw();
		//描画を保存
		gameManager->SaveDrawScreen();
		break;
		//遊んでいるとき
	case PlaySceneProgress::game:
		gameManager->DrawActor();
		//エフェクト
		DrawEffekseer3D();
		DrawEffekseer2D();
		playGameProcess->Draw();
		//描画を保存
		gameManager->SaveDrawScreen();
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
	playGameProcess->Update(gameManager);
	//遊んでいるときの処理が終了したら
	if(playGameProcess->IsEndProcess())
	{
		postGoalStaging = new PostGameEndStagingProcess(gameManager, playGameProcess->GetGameTimer());
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
	gamePrevProcess->Update(gameManager);
	//処理が終わったら
	if (gamePrevProcess->IsEndProcess())
	{
		nowProgress = PlaySceneProgress::game;
		SAFE_DELETE(gamePrevProcess);
		playGameProcess = new PlayGameProcess(gameManager);
	}
}