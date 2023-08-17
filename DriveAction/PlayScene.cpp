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
    menu->Update();
    auto menuState = menu->GetMenuState();
    //�Q�[���𒆒f����ꍇ
    if (menuState != continueGame)
    {
        nowSceneType = menuState == retry ? SceneType::RELOAD : SceneType::ESCAPE;
    }
    //menu��ʂ��J���ĂȂ��Ȃ畁�ʂ̏���
    else if (menu->IsMenuOpen() == false)
    {
        //�V�[�����Ƃ̏���
        sceneFlow->Update();
        //�������I�������
        if (sceneFlow->GetIsEndProccess())
        {
            return sceneFlow->GetNextSceneType();
        }
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
