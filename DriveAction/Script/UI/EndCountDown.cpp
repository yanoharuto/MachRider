#include "EndCountDown.h"
#include "Utility.h"
#include "UIManager.h"
#include "UIDrawer.h"
/// <summary>
/// �Q�[���I�����̃J�E���g�_�E��
/// </summary>
/// <param name="timer">�Q�[���̎c�莞�ԃ^�C�}�[</param>
EndCountDown::EndCountDown(std::weak_ptr<Timer> timer)
	:CountDown(timer)
{

	endUI = UIManager::CreateUIData(onGameEndCountDownEnd);
}
/// <summary>
/// �J�E���g�_�E���̐����ƏI����\��
/// </summary>
void EndCountDown::DrawUI() const
{
	if (uiHIndex != -1 && !isCountDownEnd)
	{
		//�I���O�ɔ����\��
		int colorValue = MAX1BYTEVALUE;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//���l��������
		UIDrawer::DrawRotaUI(countDownUIData, uiHIndex);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
	}
	else if (isCountDownEnd)//�I���������UI
	{
		UIDrawer::DrawRotaUI(endUI);
	}
}
