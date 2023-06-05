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
    fadeInFadeOut->FadeInStart();
    SoundPlayer::LoadSound(playBGM);
    menu = new Menu();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(menu);
    SAFE_DELETE(fadeInFadeOut);
    SAFE_DELETE(sceneFlow);
    SoundPlayer::StopSound(playBGM);
    DeleteUniquePtr();
}

SceneType PlayScene::Update()
{
    menu->Update();

    if (menu->GetMenuState() == retry)
    {
        if (fadeInFadeOut->GetFadeMode() != FadeMode::fadeOutStart)
        {
            fadeInFadeOut->FadeOutStart();
        }
        else if (fadeInFadeOut->GetFadeMode() == FadeMode::fadeOutStart)
        {
            fadeInFadeOut->FadeOut();
            if (fadeInFadeOut->GetFadeMode() == FadeMode::fadeOutEnd)
            {
                nowSceneType = SceneType::RELOAD;
            }
        }
    }
    //menu画面が開いてないなら普通の処理
    else if (menu->IsMenuOpen() == false)
    {

        switch (fadeInFadeOut->GetFadeMode())
        {
        case FadeMode::fadeInStart:
            fadeInFadeOut->FadeIn();
            break;
        case FadeMode::fadeInEnd:
            //シーンごとの処理
            sceneFlow->Update();
            if (sceneFlow->GetIsEndProccess())//処理が終わったら
            {
                fadeInFadeOut->FadeOutStart();
            }
            break;
        case FadeMode::fadeOutStart:
            fadeInFadeOut->FadeOut();
            break;
        case FadeMode::fadeOutEnd://フェードアウトが終わったら次のシーン
            return sceneFlow->GetNextSceneType();
            break;
        default:
            break;
        }
    }
    (*clock)->Update();
    return nowSceneType;
}

void PlayScene::Draw()
{
    sceneFlow->Draw();
    menu->Draw();
    fadeInFadeOut->Draw();
}
