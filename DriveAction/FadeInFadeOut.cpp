#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
int FadeInFadeOut::fadeValue = 0;
const int FadeInFadeOut::fadeSpeed = 10;

FadeInFadeOut::FadeInFadeOut()
{
}

FadeInFadeOut::~FadeInFadeOut()
{
}
/// <summary>
/// �t�F�[�h�C��
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeIn()
{
	fadeValue = MAX1BYTEVALUE;
	while (fadeValue > 0)
	{
		fadeValue -= fadeSpeed;//���l�ƐF��RGB����
		Fading();
	}
}
/// <summary>
/// ���񂾂񔒂��Ȃ�
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeOut()
{
	fadeValue = 0;
	while (fadeValue < MAX1BYTEVALUE)
	{
		fadeValue += fadeSpeed;//���l�ƐF��RGB����
		Fading();
	}
}
/// <summary>
/// �A�E�g���Ȃ甒���Ȃ�@�C���Ȃ����̃��f���Ƃ���������
/// </summary>
void FadeInFadeOut::Fading()
{
	//��ʂ�����������
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//���l��������
	int colorValue = MAX1BYTEVALUE;
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
	//����ʂ̓��e��\��ʂɔ��f������
	ScreenFlip();
}