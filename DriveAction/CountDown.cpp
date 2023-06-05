#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"

CountDown::CountDown(Timer* setTimer)
{
	countDownEnd = false;
	countDownUIData = UIManager::CreateUIData(countDownUI);
	timer = setTimer;
	SoundPlayer::LoadSound(countDown);
}

CountDown::~CountDown()
{
}

void CountDown::Update()
{
	switch (static_cast<int>(timer->GetLimitTime()))
	{
	case 3:
		if (!countStart)
		{
			countStart = true;
			SoundPlayer::Play2DSE(countDown);
		}
		uiNum = 2;
	break;
	case 2:
		uiNum = 1;
		break;
	case 1:
		uiNum = 0;
		break;
	case 0:
		countDownEnd = true;
		break;
	default:
		uiNum = -1;
		break;
	}
}

bool CountDown::IsCountDownEnd()
{
	return countDownEnd;
}

void CountDown::DrawUI()
{
	if (uiNum != -1)
	{
		DrawRotaGraph(countDownUIData.x, countDownUIData.y, 1, 0, countDownUIData.dataHandle[uiNum], true);
	}
}