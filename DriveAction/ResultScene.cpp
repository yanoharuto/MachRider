#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "ResultSceneFlow.h"
#include "FadeInFadeOut.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    sceneFlow = new ResultSceneFlow();
    fadeInFadeOut->FadeInStart();
}

ResultScene::~ResultScene()
{
    SAFE_DELETE(fadeInFadeOut);
    SAFE_DELETE(sceneFlow);
    DeleteUniquePtr();
}