#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
#include "RaceScreen.h"

int FadeInFadeOut::fadeValue = 0;
const int FadeInFadeOut::fadeSpeed = 10;
int FadeInFadeOut::backScreen = -1;
FadeInFadeOut::FadeInFadeOut()
{
}

FadeInFadeOut::~FadeInFadeOut()
{
}
/// <summary>
/// フェードイン
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeIn()
{
	fadeValue = MAX1BYTEVALUE;
	backScreen = -1;
	while (fadeValue > 0)
	{
		fadeValue -= fadeSpeed;//α値と色のRGB増加
		Fading();
	}
}
/// <summary>
/// だんだん白くなる
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeOut()
{
	fadeValue = 0;
	backScreen = RaceScreen::GetScreen();
	while (fadeValue < MAX1BYTEVALUE)
	{
		fadeValue += fadeSpeed;//α値と色のRGB増加
		Fading();
	}
}
/// <summary>
/// アウト中なら白くなる　インなら周りのモデルとかが見える
/// </summary>
void FadeInFadeOut::Fading()
{
	//画面を初期化する
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
	int colorValue = MAX1BYTEVALUE;
	DrawGraph(0, 0, backScreen, false);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
	//裏画面の内容を表画面に反映させる
	ScreenFlip();
}