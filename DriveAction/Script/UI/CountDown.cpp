#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UIDrawer.h"
#include "Timer.h"
/// <summary>
/// カウントダウンのUI
/// </summary>
/// <param name="setTimer">このタイマーの残り時間の3秒前からカウントダウンする</param>
CountDown::CountDown(std::weak_ptr<Timer> setTimer)
{
	isCountDownEnd = false;
	isPlayedCountSE = false;
	countDownUIData = UIManager::CreateUIData(countDownUI);
	endUI = UIManager::CreateUIData(onGameStartCountDownEnd);
	timer = setTimer;
	SoundPlayer::LoadSound(countDown);
}
/// <summary>
/// タイマーの解放
/// </summary>
CountDown::~CountDown()
{
	timer.reset();
}

/// <summary>
/// タイマーを進ませてUIの数字を変更する
/// </summary>
void CountDown::Update()
{
	switch (static_cast<int>(timer.lock()->GetRemainingTime()))//残りあと何秒
	{
	case 0:
		isCountDownEnd = true;
		break;
	case 1:
		uiHIndex = 0;
		break;
	case 2:
		uiHIndex = 1;
		break;
	case 3:
		if (!isPlayedCountSE)//初回はカウントダウンの音を鳴らす
		{
			uiHIndex = 2;
			isPlayedCountSE = true;
			SoundPlayer::Play2DSE(countDown);
		}
		break;
	} 
}
/// <summary>
/// カウントダウンと終了後のUIを描画
/// </summary>
void CountDown::DrawUI()const
{
	if (isCountDownEnd)//終了後startとかendとか出す
	{
		UIDrawer::DrawRotaUI(endUI);
	}
	else if (isPlayedCountSE)//3.2.1と数字を出していく
	{
		UIDrawer::DrawRotaUI(countDownUIData, uiHIndex);
	}
}
/// <summary>
/// カウントダウンの音が終わったら
/// </summary>
/// <returns></returns>
bool CountDown::IsPlayCountDownSound() const
{
	return SoundPlayer::IsPlaySound(countDown);
}
/// <summary>
/// カウントダウン処理が終わったら
/// </summary>
/// <returns></returns>
bool CountDown::IsCountDownEnd() const
{
	return isCountDownEnd;
}