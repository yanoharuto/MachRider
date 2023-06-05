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
/// �t�F�[�h�C��
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeIn()
{
	switch (fadeMode)
	{
	case FadeMode::fadeInStart:

		if (fadeValue > 0)
		{
			fadeValue -= fadeSpeed ;//���l�ƐF��RGB����
		}
		else
		{
			fadeMode = FadeMode::fadeInEnd;//��������������t�F�[�h�C���I��
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
/// �t�F�[�h�C���J�n
/// </summary>
void FadeInFadeOut::FadeInStart()
{
	fadeValue = MAX1BYTEVALUE;
	fadeMode = FadeMode::fadeInStart;
}
/// <summary>
/// �t�F�[�h�A�E�g�J�n
/// </summary>
void FadeInFadeOut::FadeOutStart()
{
	fadeValue = 0;
	fadeMode = FadeMode::fadeOutStart;

}
/// <summary>
/// ���񂾂񔒂��Ȃ�
/// </summary>
/// <param name="deltaTime"></param>
void FadeInFadeOut::FadeOut()
{
	switch (fadeMode)
	{
	case FadeMode::fadeOutStart:
		
		if (fadeValue < MAX1BYTEVALUE)
		{
			fadeValue += fadeSpeed;//���l�ƐF��RGB����
		}
		else
		{
			fadeMode = FadeMode::fadeOutEnd;//��������������t�F�[�h�A�E�g�I��
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
/// �t�F�[�h�A�E�g�t�F�[�h�C���̏󋵂�Ԃ�
/// </summary>
/// <returns></returns>
FadeMode FadeInFadeOut::GetFadeMode()
{
    return fadeMode;
}
/// <summary>
/// �A�E�g���Ȃ甒���Ȃ�@�C���Ȃ����̃��f���Ƃ���������
/// </summary>
void FadeInFadeOut::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//���l��������
	int colorValue = MAX1BYTEVALUE - fadeValue;
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(colorValue, colorValue, colorValue), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ɖ߂�
}