#include "EndCountDown.h"
#include "Utility.h"
#include "UIManager.h"
#include "UIDrawer.h"
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
	if (uiHIndex != -1 && !isCountDownEnd)
	{
		//終了前に薄く表示
		int colorValue = MAX1BYTEVALUE;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, aValue);//α値をいじる
		UIDrawer::DrawRotaUI(countDownUIData, uiHIndex);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
	}
	else if (isCountDownEnd)//終わった時のUI
	{
		UIDrawer::DrawRotaUI(endUI);
	}
}
