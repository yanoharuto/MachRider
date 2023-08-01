#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"

EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
}
