#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "TitleSceeneFlow.h"
#include "FadeInFadeOut.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    sceneFlow = new TitleSceeneFlow();
    fadeInFadeOut->FadeInStart();
    SoundPlayer::LoadSound(titleBGM);
}

TitleScene::~TitleScene()
{
    SAFE_DELETE(fadeInFadeOut);
    SAFE_DELETE(sceneFlow);
    SoundPlayer::StopAllSound();
    DeleteUniquePtr();
}