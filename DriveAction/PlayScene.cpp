#include "PlayScene.h"
#include "PlaySceneFlow.h"

#include "Utility.h"
#include "SoundPlayer.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
/// <summary>
/// �V��ł���Ƃ��̃V�[��
/// </summary>
PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    sceneFlow = new PlaySceneFlow();
    
    SoundPlayer::LoadSound(playBGM);
    menu = new Menu();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(sceneFlow);
    SoundPlayer::StopSound(playBGM);
}
/// <summary>
/// �Q�[����V��
/// </summary>
/// <returns></returns>
SceneType PlayScene::Update()
{
    //���j���[�Ńv���C���[������I�񂾂�
    menu->Update();
    MenuState menuState = menu->GetMenuState();
    

    switch (menuState)
    {
    case continueGame:
        //menu��ʂ��J���ĂȂ��Ȃ畁�ʂ̏���
        if (menu->IsMenuOpen() == false)
        {
            //�V�[�����Ƃ̏���
            sceneFlow->Update();
            //�������I�������
            if (sceneFlow->GetIsEndProccess())
            {
                return sceneFlow->GetNextSceneType();
            }
        }
    break;
    //�Q�[������蒼��
    case retry:
        nowSceneType = SceneType::RELOAD;
        break;
        //�^�C�g���ɖ߂�
    case returnTitle:
        nowSceneType = SceneType::TITLE;
        break;
        //�Q�[���I��
    case exitGame:
        nowSceneType = SceneType::ESCAPE;
        break;
    default:
        break;
    }
    
    return nowSceneType;
}
/// <summary>
/// ���j���[���J���Ă��鎞�ƗV��ł���Ƃ��ŏ������Ⴄ
/// </summary>
void PlayScene::Draw()const
{
    if (Menu::IsMenuOpen())
    {
         menu->Draw();
    }
    else
    {
        sceneFlow->Draw();
    }
}
