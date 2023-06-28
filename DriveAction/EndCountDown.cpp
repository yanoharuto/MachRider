#include "EndCountDown.h"
#include "Utility.h"
#include "UIManager.h"
/// <summary>
/// �Q�[���I�����̃J�E���g�_�E��
/// </summary>
/// <param name="timer"></param>
EndCountDown::EndCountDown(Timer* timer)
	:CountDown(timer)
{
	endUI = UIManager::CreateUIData(onGameEndCountDownEnd);
}
/// <summary>
/// �J�E���g�_�E���̐����ƏI����\��
/// </summary>
void EndCountDown::DrawUI() const
{
	if (uiNum != -1 && !countDownEnd)
	{
		//�I���O�ɔ����\��
		int colorValue = MAX1BYTEVALUE;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//���l��������
		DrawRotaGraph(countDownUIData.x, countDownUIData.y, 1, 0, countDownUIData.dataHandle[uiNum], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
	}
	else if (countDownEnd)
	{
		DrawRotaGraph(endUI.x, endUI.y, 1, 0, endUI.dataHandle[0], true);
	}
}
