#include "PlayScene.h"
#include "PlaySceneFlow.h"
#include "PlaySceeneProgressEnum.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Menu.h"
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

void PlayScene::Draw()
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
