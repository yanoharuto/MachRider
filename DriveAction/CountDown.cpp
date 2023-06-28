#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
/// <summary>
/// カウントダウンのUI
/// </summary>
/// <param name="setTimer"></param>
CountDown::CountDown(Timer* setTimer)
{
	countDownEnd = false;
	countDownUIData = UIManager::CreateUIData(countDownUI);
	endUI = UIManager::CreateUIData(onGameStartCountDownEnd);
	timer = setTimer;
	SoundPlayer::LoadSound(countDown);
}

CountDown::~CountDown()
{
}
/// <summary>
/// カウントダウン更新
/// </summary>
void CountDown::Update()
{
	switch (static_cast<int>(timer->GetRemainingTime()))
	{
	case 0:
		countDownEnd = true;
		break;
	case 1:
		uiNum = 0;
		break;
	case 2:
		uiNum = 1;
		break;
	case 3:
		if (!countStart)
		{
			uiNum = 2;
			countStart = true;
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
	return countDownEnd;
}
/// <summary>
/// カウントダウンと終了後のUIを描画
/// </summary>
void CountDown::DrawUI()const
{
	if (countDownEnd)//終了後startとかendとか出す
	{
		DrawRotaGraph(endUI.x, endUI.y, 1, 0, endUI.dataHandle[0], true);
	}
	else if(countStart)
	{
		DrawRotaGraph(countDownUIData.x, countDownUIData.y, 1, 0, countDownUIData.dataHandle[uiNum], true);
	}
}