#include <iostream>
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// 画面の解像度と色ビット深度を設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetZBufferBitDepth(24);
	ChangeWindowMode(true);

	// １メートルに相当する値を設定する
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
}