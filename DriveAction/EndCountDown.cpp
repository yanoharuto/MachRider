#include "EndCountDown.h"
#include "Utility.h"
#include "UIManager.h"
/// <summary>
/// ゲーム終了時のカウントダウン
/// </summary>
/// <param name="timer"></param>
EndCountDown::EndCountDown(Timer* timer)
	:CountDown(timer)
{
	endUI = UIManager::CreateUIData(onGameEndCountDownEnd);
}
/// <summary>
/// カウントダウンの数字と終わりを表示
/// </summary>
void EndCountDown::DrawUI() const
{
	if (uiNum != -1 && !countDownEnd)
	{
		//終了前に薄く表示
		int colorValue = MAX1BYTEVALUE;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//α値をいじる
		DrawRotaGraph(countDownUIData.x, countDownUIData.y, 1, 0, countDownUIData.dataHandle[uiNum], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
	}
	else if (countDownEnd)
	{
		DrawRotaGraph(endUI.x, endUI.y, 1, 0, endUI.dataHandle[0], true);
	}
}
