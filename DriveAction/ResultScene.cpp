#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "ResultSceneFlow.h"

ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    sceneFlow = new ResultSceneFlow();
}
