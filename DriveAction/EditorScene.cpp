#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"
/// <summary>
/// 編集シーンの流れをNew
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
}
