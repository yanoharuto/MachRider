#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UIDrawer.h"
/// <summary>
/// �J�E���g�_�E����UI
/// </summary>
/// <param name="setTimer">���b�v�邩</param>
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
/// �^�C�}�[��i�܂���UI�̐�����ύX����
/// </summary>
void CountDown::Update()
{
	switch (static_cast<int>(timer->GetRemainingTime()))//�c�肠�Ɖ��b
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
		if (!isPlayedCountSE)//����̓J�E���g�_�E���̉���炷
		{
			uiHIndex = 2;
			isPlayedCountSE = true;
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
	return isCountDownEnd;
}
/// <summary>
/// �J�E���g�_�E���ƏI�����UI��`��
/// </summary>
void CountDown::DrawUI()const
{
	if (isCountDownEnd)//�I����start�Ƃ�end�Ƃ��o��
	{
		UIDrawer::DrawRotaUI(endUI);
	}
	else if(isPlayedCountSE)
	{
		UIDrawer::DrawRotaUI(countDownUIData,uiHIndex);
	}
}