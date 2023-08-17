#include "EditorScene.h"
#include "DxLib.h"
#include "Utility.h"
#include "EditorSceneFlow.h"
/// <summary>
/// •ÒWƒV[ƒ“‚Ì—¬‚ê‚ğNew
/// </summary>
EditorScene::EditorScene()
    :SceneBase(SceneType::EDITOR)
{
    sceneFlow = new EditorSceneFlow();
}
