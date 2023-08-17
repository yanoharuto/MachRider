#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
#include "RaceScreen.h"
//画面が移り変わる値。高いほど白くなる
int FadeInFadeOut::fadeValue = 0;
//画面が移り変わる速度
const int FadeInFadeOut::fadeSpeed = 10;
//後ろの背景
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
	//切り替え前の画像が残ってたら消去
	if (backScreen != -1)
	{
		DeleteGraph(backScreen);
	}
	//風景が見えるようになるまで
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