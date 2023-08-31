#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UIDrawer.h"
/// <summary>
/// カウントダウンのUI
/// </summary>
/// <param name="setTimer">何秒計るか</param>
CountDown::CountDown(Timer* setTimer)
{
	isCountDownEnd = false;
	isPlayedCountSE = false;
	countDownUIData = UIManager::CreateUIData(countDownUI);
	endUI = UIManager::CreateUIData(onGameStartCountDownEnd);
	timer = setTimer;
	SoundPlayer::LoadSound(countDown);
}

/// <summary>
/// タイマーを進ませてUIの数字を変更する
/// </summary>
void CountDown::Update()
{
	switch (static_cast<int>(timer->GetRemainingTime()))//残りあと何秒
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
/// <summary>
/// カウントダウンと終了後のUIを描画
/// </summary>
void CountDown::DrawUI()const
{
	if (isCountDownEnd)//終了後startとかendとか出す
	{
		UIDrawer::DrawRotaUI(endUI);
	}
	else if(isPlayedCountSE)
	{
		UIDrawer::DrawRotaUI(countDownUIData,uiHIndex);
	}
}