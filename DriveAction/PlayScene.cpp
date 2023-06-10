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
    DeleteUniquePtr();
}

SceneType PlayScene::Update()
{
    menu->Update();
    auto menuState = menu->GetMenuState();
    //ゲームを中断する場合
    if (menuState != continueGame)
    {

        nowSceneType = menuState == retry ? SceneType::RELOAD : SceneType::ESCAPE;
    }
    //menu画面が開いてないなら普通の処理
    else if (menu->IsMenuOpen() == false)
    {
        //シーンごとの処理
        sceneFlow->Update();
        if (sceneFlow->GetIsEndProccess())//処理が終わったら
        {
            return sceneFlow->GetNextSceneType();
        }
    }
    (*clock)->Update();
    return nowSceneType;
}

void PlayScene::Draw()
{
    sceneFlow->Draw();
    menu->Draw();
}
