#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
/// <summary>
/// �J�E���g�_�E����UI
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
/// �J�E���g�_�E���X�V
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
/// �J�E���g�_�E���̉����I�������
/// </summary>
/// <returns></returns>
bool CountDown::IsPlayCountDownSound() const
{
	return SoundPlayer::IsPlaySound(countDown);
}
/// <summary>
/// �J�E���g�_�E���������I�������
/// </summary>
/// <returns></returns>
bool CountDown::IsCountDownEnd() const
{
	return countDownEnd;
}
/// <summary>
/// �J�E���g�_�E���ƏI�����UI��`��
/// </summary>
void CountDown::DrawUI()const
{
	if (countDownEnd)//�I����start�Ƃ�end�Ƃ��o��
	{
		DrawRotaGraph(endUI.x, endUI.y, 1, 0, endUI.dataHandle[0], true);
	}
	else if(countStart)
	{
		DrawRotaGraph(countDownUIData.x, countDownUIData.y, 1, 0, countDownUIData.dataHandle[uiNum], true);
	}
}