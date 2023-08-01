#include <iostream>
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// ��ʂ̉𑜓x�ƐF�r�b�g�[�x��ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetZBufferBitDepth(24);
	ChangeWindowMode(true);

	// �P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);
}