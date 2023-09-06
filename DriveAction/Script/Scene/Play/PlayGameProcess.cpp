#include "PlayGameProcess.h"
#include "ConflictManager.h"
#include "ActorControllerManager.h"
#include "GamePlayUI.h"
#include "CollectController.h"
#include "GameManager.h"
#include "SoundPlayer.h"
#include "PostGameEndStagingProcess.h"
#include "StageDataManager.h"
#include "Utility.h"
#include "StopTimer.h"
#include "Timer.h"
/// <summary>
/// プレイヤーの位置をUIに渡す
/// </summary>
/// <param name="manager">UIにプレイヤーの位置を渡す</param>
PlayGameProcess::PlayGameProcess(std::weak_ptr<GameManager> const manager)
{
	timer = StageDataManager::CreateGameTimer();
	playUI = new GamePlayUI(manager,timer);
	isEndProcess = false;
	SoundPlayer::LoadSound(playBGM);
}
/// <summary>
/// UIとタイマーの解放
/// </summary>
PlayGameProcess::~PlayGameProcess()
{
	SAFE_DELETE(playUI);
	timer.reset();
}
/// <summary>
/// 遊んでいるときの更新
/// </summary>
/// <param name="gameObject">ゲームをするときに必要なオブジェクト</param>
void PlayGameProcess::Update(std::weak_ptr<GameManager> const gameObject)
{
	//収集アイテムを全部取ったなら
	if (CollectController::IsEndGame())
	{
		timer->Stop();
	}
	//収集アイテムが全部消え終わった,制限時間の終了したなら
	if (CollectController::IsDestroyAllItem()||timer->IsOverLimitTime())
	{
		isEndProcess = true;
	}
	//BGMが鳴ってなかったら再生
	if (!SoundPlayer::IsPlaySound(playBGM))
	{
		SoundPlayer::Play2DSE(playBGM);
	}
	gameObject.lock()->Update();
	playUI->Update();
}
/// <summary>
/// 描画
/// </summary>
void PlayGameProcess::Draw() const
{
	playUI->Draw();
}
/// <summary>
/// ゲームの残り時間タイマーを渡す
/// </summary>
/// <returns> ゲームの残り時間タイマーを渡す</returns>
std::shared_ptr<Timer> PlayGameProcess::GetGameTimer()
{
	return timer;
};
