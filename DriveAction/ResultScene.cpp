#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "ResultSceneFlow.h"

ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    sceneFlow = new ResultSceneFlow();

}

ResultScene::~ResultScene()
{
    SAFE_DELETE(sceneFlow);
    DeleteUniquePtr();
}