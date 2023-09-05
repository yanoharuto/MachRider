#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "TitleSceneFlow.h"
#include "FadeInFadeOut.h"
#include "UserInput.h"
/// <summary>
/// TitleSceneFlow���m��
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    sceneFlow = new TitleSceneFlow();
}
/// <summary>
/// �^�C�g���ł̏���
/// </summary>
/// <returns>�Q�[���I����Editor���[�h��Play�V�[���ɑJ��</returns>
SceneType TitleScene::Update()
{
    //�^�C�g���ł̏���
    sceneFlow->Update();
    //�^�C�g�������I���Ȃ�Q�[����ʂ�
    if (sceneFlow->GetIsEndProcesss())
    {
        return SceneType::PLAY;
    }
    else
    {
        //�G�X�P�[�v�L�[����������I��
        if (UserInput::GetInputState(EscapeKey) == Push)
        {
            return SceneType::ESCAPE;
        }
        //W�L�[��Editor���[�h
        else if (UserInput::GetInputState(WKey) == Push)
        {
            return SceneType::EDITOR;
        }
        return nowSceneType;
    }
}