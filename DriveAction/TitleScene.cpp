#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "TitleSceeneFlow.h"
#include "FadeInFadeOut.h"
/// <summary>
/// ƒ^ƒCƒgƒ‹
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    sceneFlow = new TitleSceeneFlow();
}
