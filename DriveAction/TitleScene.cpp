#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "TitleSceneFlow.h"
#include "FadeInFadeOut.h"
/// <summary>
/// �^�C�g��
/// </summary>
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    sceneFlow = new TitleSceneFlow();
}
