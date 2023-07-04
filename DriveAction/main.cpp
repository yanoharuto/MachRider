#include <iostream>
#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "SoundPlayer.h"
#include "InitActor.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "UIDrawer.h"
//シーンを作るのに必要
SceneBase* MakeScene(SceneType _NowSceneType);

//ひとつ前のシーン
SceneType prevSceneType = SceneType::TITLE;
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
	//Effekseerを初期化する
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	//今のシーン
	SceneType nowSceneType = SceneType::TITLE;
	
	UIDrawer* uiDrawer = new UIDrawer();//画面サイズに合わせて描画できるようにする
	UserInput* userInput = new UserInput();//ユーザーの入力を所得する
	Clock* clock = new Clock();//時間
	UIManager* uiManager = new UIManager();//UI画像を取ってくる
	InitActor* initActor = new InitActor();//各actorのパラメータの初期化
	SoundPlayer* soundPlayer = new SoundPlayer();//音を流す
	EffectManager* effectManager = new EffectManager();//エフェクトの初期化
	//シーンを生成
	SceneBase* scene = new TitleScene;
	FadeInFadeOut::FadeIn();
	
	//ゲームループ
	while (ProcessMessage() == 0 && nowSceneType != SceneType::ESCAPE)
	{

#ifdef _DEBUG
		clsDx(); // printfDx の結果をリセットするための関数.
#endif	// ここでDEBUG用の処理を終了.
		
		//更新
		clock->Update();
		userInput->Update();
		nowSceneType = scene->Update();
		//画面を初期化する
		ClearDrawScreen();
		scene->Draw();//描画
		//裏画面の内容を表画面に反映させる
		ScreenFlip();
		//Updateで次のシーンに更新したなら
		if (nowSceneType != prevSceneType)
		{
			SAFE_DELETE(scene);//シーンの開放
			FadeInFadeOut::FadeOut();
			//新しいシーンの作成
			scene = MakeScene(nowSceneType);
			FadeInFadeOut::FadeIn();
		}
	}

	SAFE_DELETE(uiDrawer);
	SAFE_DELETE(uiManager);
	SAFE_DELETE(initActor);
	SAFE_DELETE(soundPlayer);
	SAFE_DELETE(effectManager);
	SAFE_DELETE(clock);
	SAFE_DELETE(userInput);
	SAFE_DELETE(scene);

	Effect_Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

/// <summary>
/// 新しく使うシーンを確保
/// </summary>
/// <param name="_NowSceneType"></param>
/// <returns></returns>
SceneBase* MakeScene(SceneType _NowSceneType)
{
	SceneBase* retScene = nullptr;
	switch (_NowSceneType)
	{
	case SceneType::RELOAD:
		retScene = MakeScene(prevSceneType);
		break;
	case SceneType::TITLE:
		retScene = new TitleScene;
		prevSceneType = SceneType::TITLE;
		break;
	case SceneType::PLAY:
		retScene = new PlayScene;
		prevSceneType = SceneType::PLAY;
		break;
	case SceneType::RESULT:
		retScene = new ResultScene;
		prevSceneType = SceneType::RESULT;
		break;
	default:
		break;
	}
	
	return retScene;
}
