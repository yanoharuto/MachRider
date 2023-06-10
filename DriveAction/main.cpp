#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"
#include "FadeInFadeOut.h"
//�V�[�������̂ɕK�v
SceneBase* MakeScene(SceneType _NowSceneType);
//�ЂƂO�̃V�[��
SceneType prevSceneType = SceneType::TITLE;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// ��ʂ̉𑜓x�ƐF�r�b�g�[�x��ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetZBufferBitDepth(24);
	

	// �P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	//Effekseer������������
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);
	//���̃V�[��
	SceneType nowSceneType = SceneType::TITLE;
	
	//�V�[���𐶐�
	SceneBase* scene = new TitleScene;
	FadeInFadeOut::FadeIn();

	UserInput* userInput = new UserInput;

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && nowSceneType != SceneType::ESCAPE)
	{

#ifdef _DEBUG
		clsDx(); // printfDx �̌��ʂ����Z�b�g���邽�߂̊֐�.
#endif	// ������DEBUG�p�̏������I��.
		
		//�X�V
		userInput->Update();
		nowSceneType = scene->Update();

		//��ʂ�����������
		ClearDrawScreen();

		scene->Draw();//�`��
		//����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
		//Update�Ŏ��̃V�[���ɍX�V�����Ȃ�
		if (nowSceneType != prevSceneType)
		{
			SAFE_DELETE(scene);//�V�[���̊J��
			FadeInFadeOut::FadeOut();
			//�V�����V�[���̍쐬
			scene = MakeScene(nowSceneType);
			FadeInFadeOut::FadeIn();
		}
		//���O�̃V�[�����L�^
		prevSceneType = nowSceneType;
	}
	
	SAFE_DELETE(userInput);
	SAFE_DELETE(scene);
	Effect_Finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

/// <summary>
/// �V�����g���V�[�����m��
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
		break;
	case SceneType::PLAY:
		retScene = new PlayScene;
		break;
	case SceneType::RESULT:
		retScene = new ResultScene;
		break;
	default:
		break;
	}
	return retScene;
}
