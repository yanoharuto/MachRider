#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
FadeInFadeOut::FadeInFadeOut()
{
	fadeMode = FadeMode::fadeInStart;
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
	switch (fadeMode)
	{
	case FadeMode::fadeInStart:

		if (fadeValue > 0)
		{
			fadeValue -= fadeSpeed ;//α値と色のRGB減少
		}
		else
		{
			fadeMode = FadeMode::fadeInEnd;//減少しきったらフェードイン終了
		}
		break;
	case FadeMode::fadeInEnd:
		break;
	default:
		fadeMode = FadeMode::fadeInStart;
		break;
	}
}
/// <summary>
/// フェードイン開始
/// </summary>
void FadeInFadeOut::FadeInStart()
{
	fadeValue = MAX1BYTEVALUE;
	fadeMode = FadeMode::fadeInStart;
}
/// <summary>
/// フェードアウト開始
/// </summary>
void FadeInFadeOut::FadeOutStart()
{
	fadeValue = 0;
	fadeMode = FadeMode::fadeOutStart;

}
/// <summary>
/// だんだん白くなる
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeOut()
{
	switch (fadeMode)
	{
	case FadeMode::fadeOutStart:
		
		if (fadeValue < MAX1BYTEVALUE)
		{
			fadeValue += fadeSpeed;//α値と色のRGB増加
		}
		else
		{
			fadeMode = FadeMode::fadeOutEnd;//増加しきったらフェードアウト終了
		}
		break;
	case FadeMode::fadeOutEnd:
		break;
	default:
		fadeMode = FadeMode::fadeOutStart;
		break;
	}
}
/// <summary>
/// フェードアウトフェードインの状況を返す
/// </summary>
/// <returns></returns>
FadeMode FadeInFadeOut::GetFadeMode()
{
    return fadeMode;
}
/// <summary>
/// アウト中なら白くなる　インなら周りのモデルとかが見える
/// </summary>
void FadeInFadeOut::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
	int colorValue = MAX1BYTEVALUE - fadeValue;
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
}